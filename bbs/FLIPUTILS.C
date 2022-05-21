/* fliputils */

#asm
 REF DSRLNK,VMBW,VSBR,VMBR,VSBW,KSCAN
 REF VWTR
#endasm

#ifdef msgpro
int tmout=20;     /*timeout, 1=10 sec*/
#else
int tmout=12;
#endif
int crlf=1,       /*carriage returns and line feeds*/
    sysop=1,      /*sysop break enabled*/
    defalt=0,     /*default RINPUT string?*/
    outflg=1,     /*output list abort flag*/
    unit=0,
    lines=24,     /*lines before 'more' prompt*/
    line=0;
char more=1; /* more prompt flags*/

#asm
EA5PAB DATA >0500,>1000,>0000,>2100
       DATA >0008
#endasm
char as[81];      /*scratch string*/

#asm
RESET  EQU  31
LDIR   EQU  13
RBRL   EQU  21
RIENB  EQU  18
RTSON  EQU  16
XBRE   EQU  22
BAUD12 DATA 417    * BAUD RATE IS 500,000/BAUD
BAUD24 DATA 208
BAUDIN DATA 1
R12SAV BSS 2
CNTRL  BYTE >83
       EVEN
#endasm

init12()
{ /* 8n1, 1200 baud */
#asm
  MOV @BAUD12,@UNIT
#endasm
 initmn();
}

init24()
{ /*8n1, 2400 baud */
#asm
  MOV @BAUD24,@UNIT
#endasm
 initmn();
}

initin()
{ /* 8n1, 500kbaud*/
#asm
  MOV @BAUDIN,@UNIT
#endasm
 initmn();
}

initmn()
{ /* initialize RS232 (baud code in UNIT) */
#asm
 MOV R12,@R12SAV
 LI R12,>002E     *CASSETTE CONTROL 2
 SBO 0            *(FOR DTR LINE)
 LI R12,>1340
 SBO  RESET
 SBZ  21
 SBZ  20
 SBZ  19
 SBZ  18          *INTERRUPT ENABLES
 SBZ  17          *NO BREAK
 SBZ  15          *TEST OFF
 LDCR @CNTRL,8
 SBZ  LDIR
 LDCR @UNIT,12
 MOV @R12SAV,R12
#endasm
}

rcvx()
{ /* recieve a char from rs/keyboard */
  /* return 0 if no char */
int k;
k=poll(0);
if (k!=0) { while (poll(0)==k); return(k);} /*wait for key release*/
#asm
       MOV R12,@R12SAV
       LI R12,>1340
       CLR R8
       TB   RBRL
       JNE  NCHAR
       STCR R8,8
       SBZ RIENB
       ANDI R8,>7F00
NCHAR  SWPB R8
       MOV @R12SAV,R12
#endasm
}

sndx(x) char x;
{ /* send and echo to screen if alphanumeric */
#asm
       MOV R12,@R12SAV
       LI R12,>1340
       MOVB @3(R14),R1
       SBO  RTSON
SND0   TB   XBRE
       JNE  SND0
       LDCR R1,8
       SBZ  RTSON
       MOV @R12SAV,R12
#endasm
if (((x>31)&&(x<127))||(x==8))
  putchar(x);
if (x==13)
  putchar('\n');
#asm
 LI R0,>0001
 MOVB @>83D4,R0
 SWPB R0
 BLWP @VWTR
 LI R0,18000 *5 MIN SCREEN-BLANK TIMEOUT
 MOV R0,@>83D6
#endasm
if (sysop) checks();
}

upper(s) char *s;
{ /* convert string s to uppercase */
int i;
  i=0;
  while (s[i]!=0)
  { if ((s[i]>96)&&(s[i]<123))
      s[i]=s[i]-32;
    i++; }
}

rinput(s) char *s;
{ /* input string from rsport or keyboard
     echo it to both, returns length in chars */
  /* allow for backspace (code 8) */
  /* adds to default string if DEFALT=1*/
  /* strip control codes */
int i,k;
i=0;
k=0;
if (defalt) {defalt=0; i=strlen(s);}
while ((k!=13)&&(i<75))
{ k=waitx();
   if (k==10)
     k==13; /* map line feed to cr */
   if (k==29)
     k==8;  /* map 'cursor left' to backspace */
   if (k==127)
     k==8;  /* map 'delete' to backspace */
   if (k!=13)
    sndx(k);
   if ((k>31)&&(k<127))
    s[i++]=k;
   if (k==8)
    if (i>0)
     i--;
    else sndx('>');
}
s[i]=0;
sndcr();
line=0;
return(i);
}

rprint(s) char *s;
{ /* prints the string to the rs/screen */
  /* allow for special codes */
int i;
outflg=1;
i=0;
while (s[i]!=0)
  sndx(s[i++]);
if (crlf) sndcr();
i=rcvx();
if (i>127) i=i-128;
if (i==19)
 while ((i!=17)&&(i!=145))
  i=waitx();
if (i==13) outflg=0;
}

sndcr()
{ /* send a carriage return/line feed */
int ocrlf;
sndx(10);
sndx(13);
line++;
if (line>=lines)
 if (more)
 { ocrlf=crlf;
   crlf=0;
   line=0;
   rprint("MORE - Press any key to continue.");
   crlf=ocrlf;
   waitx();
   sndx(10); sndx(13);
   line=0;
 }
}

waitx()
{ /* wait till a character received */
int x,t,t2;
x=0; t=0; t2=0;
line=0;
while (x==0)
{ x=rcvx();
  t++;
  if (t==5000) {t=0; t2++;}
  if ((t2==tmout/2)&&(t==0)) {rprint("Universe becoming unstable...");
                              sndx(7); sndx(7); }
  if (t2==tmout) { rprint("Universe collapses.");
#ifdef msgpro
                 getpre();
                 savusr();
                 savlas();
#endif
                 rego(); }
  if (sysop) checks();
}
return(x);
}

checks()
{ /* check for things like sysop access,
     sysop chat, dropped carrier, etc.
     called when char output or waiting for input */
int c;
#asm
 MOV R12,@R12SAV
 LI R12,>0024
 LI R0,>0600
 LDCR R0,3
 TB -13
 JNE IL#1
 MOV @R12SAV,R12
#endasm
 return(0);
#asm
IL#1
 TB -13
 JNE IL#1
 MOV @R12SAV,R12
#endasm
 sysop=0;
 rprint("Flipper's here...just a second...");
 puts("\n\nWhat now, Flip?\n");
 puts("-------------\n");
 puts("1) enter chat mode\n");
 puts("2) boot user off\n");
 puts("3) enter sysop menu\n");
 puts("4) set RS to 1200 baud\n");
 puts("5) set RS to 2400 baud\n");
 puts("6) set RS to 'infinite'\n");
 puts("0) return control to user\n");
 puts("\n\nCurrent user is:");
 puts(name);
 puts("\n");
 c=0;
 while ((c<48)||(c>54))
  c=getchar();
 switch(c)
{ case 48:rprint("Flipper has returned control to you.");
          sysop=1;
          return(0); break;
  case 49:chat();
          break;
  case 50:rprint("You have been BOOTED!");
          rego();
          break;
  case 51:strcpy(as,"DSK5.SYS");
          ea5ld();
  case 52:init12(); rprint("Set to 1200 baud."); break;
  case 53:init24(); rprint("Set to 2400 baud."); break;
  case 54:initin(); rprint("Set to infinite.."); break;
} sysop=1; }

chat()
{ /* do sysop chat mode */
int k,c;
rprint("Flipper swims up to chat...");
puts("Press ~ to exit...\n");
k=0;
while (k!=64)
{ k=poll(0);
  if ((k)&&(k!='~')) { if (k==13) sndx(10); while (poll(0)==k); }
  if (k) sndx(k);
#asm
       MOV R12,@R12SAV
       LI R12,>1340
       CLR R8
       TB   RBRL
       JNE  NCHAQ
       STCR R8,8
       SBZ RIENB
       ANDI R8,>7F00
NCHAQ  SWPB R8
       MOV R8,@UNIT
       MOV @R12SAV,R12
#endasm
  if (unit==13) sndx(10);
  if (unit) sndx(unit);
}
sndcr();
rprint("Flipper returns to the sea...you have control.");
}

clrrs()
{ /*clear all incoming characters from rs port*/
int f;
f=0;
while (f<5)
{ if (rcvx()) { f=0; while (rcvx());}
  delay(200);
  f++;}
}

delay(i) int i;
{ while (i--)
  { i++; i--; }
}

rego()
{/* restart the BBS from scratch*/
int c,unit;
hangup();
if (unit) fclose(unit);
unit=fopen("DSK5.ONLINE","w");
if (unit==0) exit(50);
fputs("***",unit);
c=fclose(unit); if (c==0) exit(50);
#asm
 LWPI >83E0
 LIMI 2
 BLWP @>0000
#endasm
}

hangup()
{/*hangup the modem*/
#asm
 MOV R12,@R12SAV
 LI R12,>002E
 SBZ 0
 CLR R0
HGNLP
 DEC R0
 JNE HGNLP
 SBO 0
 MOV @R12SAV,R12
#endasm
}

ea5ld()
{ /*load an EA#5 program, name in AS*/
int unit;
#asm
 LI R0,>F89
 MOV R0,@>8356
 LI R0,>F80
 LI R1,EA5PAB
 LI R2,40
 BLWP @VMBW
 BLWP @DSRLNK
 DATA 8
 CLR R1
 LI R0,>F81
 BLWP @VSBR
 CI R1,0
 JNE A5E
 B @NO5ERR
A5E
#endasm
rprint("Unable to load module! Attempting reboot...");
unit=fopen("DSK5.FEEDBACK","a");
if (unit!=0)
{ fputs("FEEDBACK FROM SYSTEM",unit);
  fputs("--------------------",unit);
  fputs("Was unable to load the following module:",unit);
  fputs(as,unit);
  fclose(unit);
}
#asm
 LWPI >83E0
 LIMI 2
 BLWP @>0000
#endasm
}

#asm
NO5ERR
 LI R0,>3000
 LI R1,NO5ER2
 LI R2,DONEA5-NO5ER2
EA5LP
 MOVB *R1+,*R0+
 DEC R2
 JNE EA5LP
 LI R0,>3500
 LI R1,EA5PAB
 LI R2,40
EA5LP2
 MOV *R1+,*R0+
 DEC R2
 JNE EA5LP2
 B @>3000
NO5ER2
 LI R0,>1000
 LI R1,>2900
 LI R2,6
 BLWP @VMBR
 LI R0,>1006
 MOV @>2904,R1
 MOV @>2902,R2
 AI R2,-6
 BLWP @VMBR
 MOVB @>3511,R0
 AI R0,>0100
 MOVB R0,@>3511
 MOV @>2900,@>2900
 JNE MOREA5
 B @>A000
MOREA5
 LI R0,>F80
 LI R1,>3500
 LI R2,40
 BLWP @VMBW
 LI R0,>F89
 MOV R0,@>8356
 BLWP @DSRLNK
 DATA 8
 JMP NO5ER2
DONEA5
#endasm
