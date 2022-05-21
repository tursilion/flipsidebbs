/*Flip Side Loader - front-door v2.0 */

char name[81];
char fido[15]="TSYNCH = AEH";
int fl,send,check,error;

#asm
 COPY "DSK1.XMODEM1"
#endasm

#include "dsk2.stdio"
#include "dsk1.fliputils"
#include "dsk1.stringfns"

main()
{ /*just gets the user up and going*/
int c,z;
char bs[80];
#asm
 LI R0,>0500
 MOVB R0,@>8374 *SET KEYBOARD MODE
#endasm
puts("Flip Side Loader - Horizon boot routine v2.0\n");
puts("and Fidonet mail receiver\n");
puts("by Mike Ward\n");
unit=fopen("dsk5.config","r");
fclose(unit);
unit=fopen("dsk5.config","r");
if (unit!=0)
{
fgets(bs,80,unit);
fclose(unit);
crlf=0;
init24();
clrrs();
sndx(13);
if (bs[0]=='A')
{rprint(bs);
 sndx(13);
 clrrs();
 waitx();
 clrrs();
}
crlf=1;
}
answer();
if (index(as,"24")==0) init12(); else init24();
c=0;
while ((c!=27)&&(c!=46))
{sndx(13); sndx(13);
 rprint("All systems go. Press <esc> or <.> for reality breach.");
 z=0; fl=1;
 while (fl)
 {
   c=waitx(); if (c>127) c=c-128;
   fl=0;
   if (c==fido[z])
   { z++; fl=1;
     if (z==6) {c=27; fl=0;}
   }
 }
}
if (z==6) fidont();
rprint("Loading system...");
unit=fopen("dsk5.online","w");
fputs("---",unit);
fclose(unit);
strcpy(as,"DSK5.FLP");
ea5ld();
}

answer()
{/*pickup the phone..no biggie*/
int flag2;
char c;
flag2=1;
while (flag2)
{ puts("\nWaiting for call...\n");
  while (rcvx()==0);
  clrrs();
  crlf=0;
  rprint("ATA");
  sndx(13);
  crlf=1;
  c=0;
  while ((c=waitx())!=13);
  rinput(as);
  if (index(as,"CAR")==0) flag2=0;
  else clrrs();
}}

fidont()
{ /*handle a FIDO mail call*/
xr0(); /*xmodem receive packet*/
if (error) err();
for (fl=30000; fl>0; fl--);
clrrs();
unit=fopen("dsk5.feedback","a");
fputs("Successfully received Fidopacket",unit);
fclose(unit);
s3();
rego();
}

err()
{/*an error occurred...drat!*/
unit=fopen("dsk5.feedback","a");
fputs("Error while transferring FIDO!",unit);
fclose(unit);
rego();
}

s3()
{/*send step 3*/
int qw,qe;
qw=0; qe=0;
clrrs();
crlf=0;
while (qe==0)
{rprint(fido);
 fl=0;
 while (fl==0)
 {#asm
 MOV R12,@R12SAV
 LI R12,>1340
 CLR R1
 TB RBRL
 JNE NCHR2
 STCR R1,8
 ANDI R1,>7F00
NCHR2 SWPB R1
 MOV R1,@FL
 MOV @R12SAV,R12
#endasm
 qw++;
 if (qw==30000) err();
 }
if ((fl=='C')||(fl==21)) qe=1;
else clrrs();
}
xs1();
if (error) err();
unit=fopen("dsk5.feedback","a");
fputs("Packet sent Ok",unit);
fclose(unit);
}

xr0()
{ /*xmodem receive packet*/
strcpy(as,"MAILIN");
check=0;
send=-1;
xmodem();
}

xs1()
{ /*xmodem send packet*/
strcpy(as,"MAILOUT");
check=0;
if (fl=='C') check=-1;
send=0;
xmodem();
}

xmodem()
{/*do the actual xmodem*/
#asm
 COPY "DSK1.XMODEM2"
#endasm
}
