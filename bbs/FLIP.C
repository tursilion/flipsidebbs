/*Flip Side BBS by Mike Ward
       DSK2.STDIO
       DSK1.FLIPUTILS
       DSK1.STRINGFNS         */

int unum,m_1;

char name[81],creds[5];

char c,k,pw[81];
char sl[15],hl[10],lm[81];
char nmask[81];

#include "dsk2.stdio"
#include "dsk1.fliputils"
#include "dsk1.stringfns"

main()
{/*the main program*/
puts("\n\n The FLIP Side! BBS By Mike Ward\n");
puts("Written in c99. version 1.3\n");
unit=fopen("DSK5.ONLINE","r");
if (unit==0) {rprint("ONLINE file corrupted or missing! please hang up");
              exit(0); }
fgets(name,80,unit);
fclose(unit);
if (strcmp(name,"***")==0) rego();
if (strcmp(name,"---")) reload(); else
{initsy();
title();
login();
unit=fopen("DSK5.ONLINE","w");
if (unit==0) {rprint("RAMdisk bad..fatal error."); rego();}
fputs(name,unit);
c=fclose(unit);
if (c==0) {rprint("Can't close ONLINE file! Fatal error."); rego();}
}
while (m_1)
  menu();
logoff();
}

initsy()
{ /* initialize the Flip Side BBS */
sysop=1;
m_1=1;
unit=fopen("DSK5.CONFIG","r");
if (unit==0) {creds[0]='9'; creds[1]=0;}
else {fgets(as,2,unit);
      fgets(as,70,unit);
      fclose(unit);
      creds[0]=as[0];
      creds[1]=0;
      strcpy(nmask,&as[2]);
}    }

title()
{ /* draws the title page */
unit=fopen("dsk5.title","r");
if (unit==0) return(0); /*no title?*/
while ((!feof(unit))&&(outflg))
{ fgets(as,81,unit);
  rprint(as);
}
fclose(unit);
}

login()
{ /* get the user to log in */
int flag,a,b;
sndcr();
flag=0;
while (flag==0)
{ crlf=0;
name[0]=0;
while (name[0]==0)
{rprint("Please enter your handle:");
crlf=1;
rinput(name); }
upper(name);
for (a=0; name[a]!=0; a++)
 if (name[a]>127) name[a]=name[a]-128;
while (name[0]<33)
 for (a=1; name[a-1]!=0; a++)
  name[a-1]=name[a];
a=a-2;
while (name[a]<33)
 name[a--]=0;
sndcr();
valid(&flag); }
if (flag==1)
{ crlf=0;
rprint("Hi there, ");
crlf=1;
rprint(name);
unit=fopen("DSK5.CREDS","w");
if (unit) {fputs(creds,unit);
           fclose(unit);}
logsin();
bullet(); }
else
{ rprint("LIAR!!! GO TO HELL!!");
rego();}
}

menu()
{ /* the main menu routine...exit from here means logoff*/
sndcr(); sndcr();
if ((c==13)||(c==15)||(hl[0]=='F')) {
rprint("The Flip Side, main menu");
rprint("------------------------");
sndcr();
rprint("1) Message chatter");
rprint("2) Online diversions");
rprint("3) Utility");
rprint("4) Call for Flipper");
rprint("5) Feed Flipper");
rprint("6) Sysop menu (for sysops)");
rprint("7) Get out of here!");
sndcr();
rprint("Press the # of your choice"); }
else rprint("[M,O,U,C,F,S,G,?]");
c=0;
while (((c<49)||(c>55))&&(pos(c,"MOUCFSGmoucfsg?")==0)&&(c!=13))
 {c=waitx(); if (c>96) c=c-32;}
if (pos(c,"MOUCFSG")!=0)
 c=pos(c,"MOUCFSG");
if (c>48) c=c-48;
switch(c)
{ case 1:msgbas(); break;
  case 2:drload(); break;
  case 3:utils();  break;
  case 4:pager();  break;
  case 5:feedbk(); break;
  case 6:sysld(); break;
  case 7:off();  break;
}}

logoff()
{/* say goodbye, hang up, fix stats, etc.
    VALIDATION must already be done! */
sndcr();
sndcr();
crlf=0;
rprint("Goodbye, ");
crlf=1;
rprint(name);
sndcr();
rprint("Returning you to reality...");
rego();
}

pos(c,x) int c; char x[];
{ /*return pos of char c in string x*/
int q1,q2;
q1=0;
for (q2=0; x[q2]; q2++)
  if (x[q2]==c) q1=q2+1;
return(q1);
}

valid(f) int *f;
{/*valid user's name...return 0 for new
name, 1 for ok and 2 for illegal logon*/
char nstr[4];
unum=0;
rprint("Scanning...");
unit=fopen("DSK5.USERS","r");
if (unit==0) {rprint("No user file!! Fatal error!!"); rego();}
fgets(as,80,unit);
while ((!feof(unit))&&(strcmp(name,as)!=0))
{ fgets(as,80,unit); unum++;}
fclose(unit);
if (strcmp(name,as)!=0)
{ rprint(name);
  rprint("That name was not found. Are you a new user?");
  c=0; while ((c!=89)&&(c!=78))
  { c=waitx(); if (c>97) c=c-32; }
  if (c==78) *f=0;
  else
  { unum++;
    newusr();
    *f=1; }
}
else
{ in2str(unum,nstr);
  strcpy(as,"DSK5.USER");
  strcat(as,nstr);
  unit=fopen(as,"r");
  if (unit==0)
  { rprint("Your user file vanished!! Fatal error!"); rego();}
  fgets(pw,80,unit);
  fgets(sl,15,unit);
  fgets(hl,10,unit);
  fgets(lm,80,unit);
  fclose(unit);
  rprint("Oh yeah? What's your password?");
  pinput(as);
  upper(as);
  if (strcmp(as,pw)==0) *f=1;
  if (*f!=1)
  { rprint("Maybe not. Try again.");
    pinput(as);
    upper(as);
    if (strcmp(as,pw)==0) *f=1;
  }
  if (*f!=1)
  { rprint("Last chance. Make it good.");
    pinput(as);
    upper(as);
    if (strcmp(as,pw)==0) *f=1;
  }
  if (*f!=1) *f=2;
}}

utils()
{/*do the user utilities*/
char bs[81];
sndcr();
rprint("Your current stats");
rprint("------------------");
crlf=0;
rprint("Name:");
rprint(name);
sndcr();
rprint("Password: [not shown]");
sndcr();
rprint("Main menu help level:");
rprint(hl);
sndcr();
rprint("Security level:");
rprint(sl);
sndcr();
crlf=1;
sndcr();
c=13;
while ((c==13)||(c==63))
{rprint("1 - change password");
rprint("2 - change help level");
rprint("3 - see user list");
rprint("4 - see last callers");
rprint("5 - change 'more' prompt");
rprint("0 - exit to main");
sndcr();
c=0;
while ((pos(c,"123450?")==0)&&(c!=13))
c=waitx();
sndcr();
switch(c)
  { case 49:rprint("Enter new password.");
            rinput(bs);
            upper(bs);
            rprint("Enter it again...");
            pinput(as);
            upper(as);
            if (strcmp(bs,as)==0)
            {rprint("New password accepted");
             strcpy(pw,as);
             savusr();
            }
            else rprint("No match! Not changed.");
            break;
    case 50:if (hl[0]=='B')
              strcpy(hl,"FULL");
            else
              strcpy(hl,"BRIEF");
            crlf=0;
            rprint("Help level now:");
            crlf=1;
            rprint(hl);
            savusr();
            break;
    case 51:unit=fopen("DSK5.USERS","r");
            if (unit)
            { while ((!feof(unit))&&(outflg))
              { fgets(as,80,unit);
                rprint(as);
              }
              fclose(unit);
              if (outflg==0) rprint("***Aborted***");
            } else rprint("Error!"); break;
    case 52:unit=fopen("DSK5.FEEDBACK","r");
            if (unit)
            { while((!feof(unit))&&(outflg))
              { fgets(as,80,unit);
                if (as[0]=='*') rprint(as);
              }
              fclose(unit);
              if (outflg==0) rprint("***Aborted***");
            } else rprint("Error!"); break;
    case 53:crlf=0; rprint("'More' prompt at ");
            sndx(hl[5]); sndx(hl[6]);
            crlf=1; rprint(" lines. (0=off)");
            rprint("Enter new value, <cr> to abort");
            rinput(as);
            if (as[1]==0) {as[2]=0; as[1]=as[0]; as[0]='0';}
            if ((as[0]>='0')&&(as[0]<='9'))
             if ((as[1]>='0')&&(as[1]<='9'))
             {hl[5]=as[0]; hl[6]=as[1];
              if ((as[0]=='0')&&(as[1]=='0'))
               hl[7]='N'; else hl[7]='Y';
               hl[8]=0; savusr();
             } break;
} if (c!=48) c=13;
}}

#asm
PAG#D  DATA >059F,>BFDF,>FFE3,>0109,>8E01
       DATA >A402,>C501,>90B6,>D306,>0391
       DATA >B7D4,>0203,>92B8,>D501,>05A7
       DATA >0493,>B0D6,>0203,>94B1,>D703
       DATA >0395,>B2D8,>0406,>CA02,>96B3
       DATA >D0FF
       DATA >0303,>97B4,>D102,>0398
       DATA >B5D2,>0105,>8503,>90B6,>D302
       DATA >0391,>B7D4,>0303,>92B8,>D504
       DATA >05A4,>0293,>B0D6,>0303,>94B1
       DATA >D702,>0395,>B2D8,>0105,>C501
       DATA >96B3,>D002,>0397,>B4D1,>0303
       DATA >98B5,>D204,>039F,>BFDF,>0000
H01    BYTE >01
       EVEN
#endasm

pager()
{/*page the sysop*/
int q;
sndcr();
crlf=0;
rprint("Hey Flipper! ");
rprint(name);
sndcr();
rprint("wants to talk to you!!");
sndcr(); sndcr();
rprint("Paging");
for (q=0; q<5; q++)
{ rprint(".");
#asm
 CLR R0
 LI R1,PAG#D
 LI R2,120
 BLWP @VMBW
 MOV R0,@>83CC
 SOCB @H01,@>83FD
 MOVB @H01,@>83CE
WBE#1
 LIMI 2
 LIMI 0
 MOVB @>83CE,@>83CE
 JNE WBE#1
#endasm
}
crlf=1; sndcr();
rprint("Well...he can't stand those chimes,");
rprint("so if he's around he'll break in.");
rprint("If he doesn't, well.....I tried!");
rprint("Leave feedback if no answer.");
}

off()
{/*validate log-off option*/
sndcr();
rprint("WHAT?! Leave the Flip Side? Are you sure?? ([Y]/n)");
c=0;
while ((c!=89)&&(c!=78)&&(c!=121)&&(c!=110)&&(c!=13))
 c=waitx();
if ((c==89)||(c==121)||(c==13))
{m_1=0;
 sndcr();
 crlf=0;
 rprint("OK...bye ");
 rprint(name);
 crlf=1;
 rprint(". Call again");
}
else
 rprint("Temporary insanity...");
}

in2str(x,s) int x; char s[];
{ /*convert int x to 2 digit string s*/
int q;
if (x>99) x=99;
q=x/10;
s[0]=q+48;
s[1]=x-q*10+48;
s[2]=0;
}

newusr()
{/*create a new user, update disk files*/
char junk[81],j2[5];
rprint("Welcome to the Flip Side!!");
rprint("First thing you must do as a new user is");
rprint("fill out the new user questionaire. You are");
rprint("hereby warned to make it interesting.");
nquest();
rprint("Good! You may have some potential after all!");
rprint("Please select the password you wish to use.");
rprint("It is not case sensitive");
sndcr();
as[1]=1; junk[1]=2;
while (strcmp(as,junk)!=0)
{ rinput(as);
  upper(as);
  rprint("Enter it again, just to be safe.");
  pinput(junk);
  upper(junk);
  if (strcmp(as,junk)!=0) rprint("No match! Start over. Enter your password");
}
rprint("Great! Sec while I update the files...");
unit=fopen("DSK5.USERS","a");
if (unit==0) {rprint("Bah! User file screwed! Fatal error."); rego();}
fputs(name,unit);
c=fclose(unit);
if (c==0) {rprint("Can't add you! error!"); rego();}
strcpy(pw,as);
strcpy(sl,"NORMAL");
strcpy(hl,"FULL");
strcpy(lm,nmask);
savusr();
rprint("All done!!");
sndcr();
}

reload()
{/* load the online user's stats*/
char nstr[4];
unum=0;
rprint("One moment...");
unit=fopen("DSK5.USERS","r");
if (unit==0) {rprint("No user file!! Fatal error!!"); rego();}
fgets(as,80,unit);
while ((!feof(unit))&&(strcmp(name,as)!=0))
{ fgets(as,80,unit); unum++;}
fclose(unit);
if (strcmp(name,as)!=0)
{ rprint(name);
  rprint("You've vanished from the files!! Fatal error");
  rego();
}
else
{ in2str(unum,nstr);
  strcpy(as,"DSK5.USER");
  strcat(as,nstr);
  unit=fopen(as,"r");
  if (unit==0)
  { rprint("Your user file vanished!! Fatal error!"); rego();}
  fgets(pw,80,unit);
  fgets(sl,15,unit);
  fgets(hl,10,unit);
  fgets(lm,80,unit);
  fclose(unit);
}}

#include "dsk1.flip2.c"
