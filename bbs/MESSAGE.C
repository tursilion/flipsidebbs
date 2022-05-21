/* MSG PROCESSOR VERSION 2.0 for the
FLIP Side BBS */

#define msgpro haha
int unum,m_1,zerofl,new;
int thred,x1,x2,x3,qscan=0;
int base,obase,maxmsg;
char trdnum[4],svmnum[4];
char dos[10],oldm2[80],fm2[80];
char basen[80];
char name[81],temp[81];
char c,k,pw[81],sl[15],hl[10],lm[5],lm2[80];
char mnum[4],oldm[4],bs[81];
char date[81],fm[5];

#include "dsk2.stdio"
#include "dsk1.fliputils"
#include "dsk1.stringfns"

main()
{/*the main routine*/
 unit=fopen("DSK5.ONLINE","r");
 if (unit==0) rego();
 fgets(name,80,unit);
 fclose(unit);
 getusr();
 unit=fopen("DSK5.LASTMESS","r");
 if (unit==0) {for (c=0; c<60; c++) oldm2[c]='0'; oldm2[60]=0;}
 else
 {fgets(oldm2,80,unit);
  fclose(unit); }
 unit=fopen("DSK5.FIRSTMESS","r");
 if (unit==0) {for (c=0; c<60; c++) fm2[c]='0'; fm2[60]=0;}
 else {fgets(fm2,80,unit); fclose(unit);}
 dos[0]='!'; /*flag for first entry*/
 base=0;
 unit=fopen("DSK5.DATE","r");
 if (unit==0) strcpy(date,"No Date");
 else
 {fgets(date,80,unit);
  fclose(unit); }
 m_1=1;
 while (m_1)
  menu();
 getpre();
 savusr();
 savlas();
 strcpy(as,"DSK5.FLP");
 ea5ld();
}

savlas()
{/*save last&first message #*/
unit=fopen("DSK5.LASTMESS","w");
fputs(oldm2,unit);
fclose(unit);
unit=fopen("DSK5.FIRSTMESS","w");
fputs(fm2,unit);
fclose(unit);
}

getusr()
{/*load the user stats from the name only*/
char nstr[4];
unum=0;
unit=fopen("DSK5.USERS","r");
if (unit==0) {rprint("No user file!! Fatal error!"); rego();}
fgets(as,80,unit);
while ((!feof(unit))&&(strcmp(name,as)!=0))
{ fgets(as,80,unit); unum++;}
fclose(unit);
if (strcmp(name,as)!=0) {rprint("Not found! fatal error!"); rego();}
in2str(unum,nstr);
strcpy(as,"DSK5.USER");
strcat(as,nstr);
unit=fopen(as,"r");
if (unit==0) {rprint("No user file! Fatal error!"); rego();}
fgets(pw,80,unit);
fgets(sl,15,unit);
fgets(hl,10,unit);
fgets(lm2,80,unit);
fclose(unit);
lines=(hl[5]-48)*10+(hl[6]-48);
more=(hl[7]=='Y');
}

savusr()
{/*re-save current user*/
char nstr[4];
in2str(unum,nstr);
strcpy(as,"DSK5.USER");
strcat(as,nstr);
unit=fopen(as,"w");
if (unit==0) {rprint("Unable to save user! Fatal error!"); rego();}
fputs(pw,unit);
fputs(sl,unit);
fputs(hl,unit);
fputs(lm2,unit);
c=fclose(unit);
if (c==0) {rprint("Can't close file! Fatal error!"); rego();}
}

in2str(x,s) int x; char s[];
{/*convert int x to 2 digit string*/
if (x>99) x=99;
s[0]=x/10+48;
s[1]=x%10+48;
s[2]=0;
}

pos(c,x) char x[],c;
{/*return location of c in x*/
int y;
y=0;
if (c>91) c=c-32;
while ((x[y]!=c)&&(x[y])) y++;
if (x[y]==0) return(0);
else return(++y);
}

menu()
{/*do menu until m_1=0*/
char erg[4];
sndcr();
getpre();
if ((hl[0]!='B')||(c=='?'))
{rprint("Mini Message Processor v2.0");
 rprint("----------------------");
 rprint("[C]hange message base");
 rprint("[R]ead single");
 rprint("[F]orward read");
 rprint("[B]ackward read");
 rprint("[N]ew read");
 rprint("[!]Quickscan New");
 rprint("[E]nter message");
 rprint("[Q]uit to main");
 sndcr(); }
rprint(basen);
crlf=0;
rprint("Last message you read:");
rprint(lm);
sndcr();
rprint("First message #");
rprint(fm);
sndcr();
rprint("Last message  #");
x1=oldm[0];
x2=oldm[1];
x3=oldm[2]-1;
if (x3<48) {x2--; x3=57; if (x2<48) {x1--; x2=57;}}
sndx(x1);
sndx(x2);
sndx(x3);
sndcr();
ncount();
thred=0;
c=0;
while ((pos(c,"CRFBN!EQ?")==0)&&(c!=13))
{rprint("[C,R,F,B,N,!,E,Q,?]");
 c=waitx();
 if (c>96) c=c-32; }
switch (c)
{ case 'C':select(); break;
  case 'R':read(); break;
  case 'F':forwrd(); break;
  case 'B':backwd(); break;
  case 'N':newrd(); break;
  case 'E':enter(); break;
  case '!':quick(); break;
  case 'Q':m_1=0;
           rprint("Returning to main...");
           break;
}}

ncount()
{/*sets FM if out of range, and displays # new*/
if (strcmp(oldm,fm)<0)
{if ((strcmp(lm,fm)<0)&&(strcmp(oldm,lm)<0)) strcpy(lm,fm);}
else
{if (strcmp(lm,fm)<0) strcpy(lm,fm);}
if ((strcmp(lm,oldm)>0)&&(strcmp(oldm,fm)>0)) strcpy(lm,fm);
rprint("There are ");
x1=oldm[0]-lm[0];
x2=oldm[1]-lm[1];
x3=oldm[2]-lm[2];
if (strcmp(lm,oldm)<0)
{ x3=x3-1;
  if (x3<0) {x2--; x3=x3+10;}
  if (x2<0) {x1--; x2=x2+10;}
}
else
{ x3=x3+10;
  x2=x2+9;
  x1=x1+9;
  if (x3>9) {x2++; x3=x3-10;}
  if (x2>9) {x1++; x2=x2-10;}
}
sndx(x1+48);
sndx(x2+48);
sndx(x3+48);
crlf=1; new=x1*100+x2*10+x3;
rprint(" new messages");
}

cntmsg()
{/*calculate # messages*/
int z;
x1=oldm[0]-fm[0];
x2=oldm[1]-fm[1];
x3=oldm[2]-fm[2];
if (strcmp(fm,oldm)<0)
{ x3=x3-1;
  if (x3<0) {x2--; x3=x3+10;}
  if (x2<0) {x1--; x2=x2+10;}
}
else
{ x3=x3+10;
  x2=x2+9;
  x1=x1+9;
  if (x3>9) {x2++; x3=x3-10;}
  if (x2>9) {x1++; x2=x2-10;}
}
z=x1*100+x2*10+x3;
return(z);
}

msginc(x) char x[];
{/*inc 3 digit string*/
x[2]=x[2]+1;
if (x[2]>'9')
{ x[1]=x[1]+1; x[2]='0';
  if (x[1]>'9')
  { x[0]=x[0]+1; x[1]='0';
    if (x[0]>'9') x[0]='0';
  }
}}

msgdec(x) char x[];
{/*dec 3 digit string*/
x[2]=x[2]-1;
if (x[2]<'0')
{ x[1]=x[1]-1; x[2]='9';
  if (x[1]<'0')
  { x[0]=x[0]-1; x[1]='9';
    if (x[0]<'0') x[0]='9';
  }
}}

read()
{/* read individual message*/
rprint("Read a single message. Enter message number");
getnum();
c='A';
while (c=='A')
  disply();
}

forwrd()
{/*read forward*/
rprint("Forward read. Start at which number? (c/r=first)");
getnum();
if (zerofl) strcpy(mnum,fm);
fwdrd2();
}

fwdrd2()
{/*rest of forward read/new read*/
c=0;
while (c!='Q')
{ disply();
  if (c!='A')
    msginc(mnum);
}}

backwd()
{/*read backwards*/
rprint("Backward read. Start at which number? (c/r=last)");
getnum();
if (zerofl) {strcpy(mnum,oldm); msgdec(mnum);}
c=0;
while (c!='Q')
{ disply();
  if (c!='A')
    msgdec(mnum);
}}

newrd()
{/*read new*/
if (new)
{ rprint("New messages.");
  strcpy(mnum,lm);
  fwdrd2();
}}

enter()
{/*enter a message*/
int ok,unit2,bs[80];
strcpy(as,dos);
strcat(as,oldm);
rprint("sec...");
unit=fopen(as,"w");
if (unit==0) {rprint("Unable to open message file."); return(0);}
crlf=0; ok=0;
while (!ok)
{rprint("To:");
 rinput(temp);
 sndcr();
 upper(temp);
 strcpy(as,"To:");
 ok=1;
 if (strcmp(temp,"ALL"))
 { rprint("Private? (y/N)");
   c=waitx();
   if (c>91) c=c-32;
   if (c=='Y') {rprint("Yep!"); strcat(as,"!");
                unit2=fopen("dsk5.users","r");
                ok=0;
                while (!feof(unit2))
                {fgets(bs,70,unit2);
                 if (strcmp(bs,temp)==0) ok=1;
                }
                fclose(unit2);
                if (ok==0) rprint("No such user!");
               }
    else rprint("Nah.");
}}
sndcr();
crlf=1;
strcat(as,temp);
enter2();
}

enter2()
{/*part 2 of enter message/reply*/
int z,y,o,dne,ln,dn2; char bs[80];
char msbuf[50][80];
ln=0;
strcpy(&msbuf[ln++][0],as);
strcpy(&msbuf[ln][0],"From:");
strcat(&msbuf[ln++][0],name);
strcpy(&msbuf[ln][0],"Date:");
strcat(&msbuf[ln++][0],date);
if (c=='R') {strcpy(&msbuf[ln][0],"Reply to ");
             strcat(&msbuf[ln++][0],mnum);
            }
if (as[3]=='!') strcpy(&msbuf[ln++][0],"<PRIVATE MESSAGE>");
strcpy(&msbuf[ln++][0]," ");
rprint("Enter your message now. Enter a blank line to end.");
dne=0;
while (!dne)
{while (as[0])
 { if (defalt==0) sndx('>');
   z=rinput(as);
   if ((z==75)&&(as[74]!=' '))
   { y=z;
     while ((as[--y]!=32)&&(y>40));
     if (y>40)
     { as[y++]=0;
       o=0;
       defalt=1; sndx('>');
       while (y<z)
        sndx((bs[o++]=as[y++]));
       bs[o]=0;
     }
   }
   strcpy(&msbuf[ln++][0],as);
   if (ln==45) rprint("**5 lines left!**");
   if (defalt==1) strcpy(as,bs);
   if (ln==50) {rprint("***Message buffer full***"); as[0]=0;}
 }
 sndcr();
 dn2=0;
 while (!dn2)
 {c=0;
  while (!pos(c,"CASLE"))
  { rprint("[C]ontinue, [A]bort, [S]ave, [L]ist, [E]dit?");
    c=waitx(); if (c>96) c=c-32;}
  as[0]=5;
  switch(c)
  { case 'C':rprint("Continue your message.");
             dn2=1; ln--; break;
    case 'A':rprint("*Abort* You sure? (y/N)");
             c=waitx();
             if ((c=='y')||(c=='Y'))
             { dne=1; dn2=1;
               rprint("Aborting...");
               fclose(unit);
               strcpy(as,dos);
               strcat(as,oldm);
               fdelete(as);
             } break;
    case 'S':rprint("Saving...");
             dne=1; dn2=1;
             for (z=0; z<ln; z++)
               fputs(&msbuf[z][0],unit);
             fclose(unit);
             msginc(oldm);
             y=cntmsg();
             if (y>maxmsg)
             { strcpy(as,dos);
               strcat(as,fm);
               fdelete(as);
               msginc(fm);
             } break;
    case 'L':for (z=0; z<ln; z++)
              rprint(&msbuf[z][0]);
             break;
    case 'E':z=4; c='?'; y=1;
             while (c!='Q')
             { if (c=='?')
               {rprint("Editor:[A]head, [B]ack, [C]hange line");
                rprint("[I]nsert line, [D]elete line, [Q]uit");
                rprint("[0-9] change step (0=10)");
               }
               in2str(z,as); strcat(as,":");
               rprint(as);
               rprint(&msbuf[z][0]);
               c=0;
               while (!pos(c,"ABCIDQ?"))
               { rprint("[A,B,C,I,D,Q,0-9,?]");
                 c=waitx(); if (c>96) c=c-32;
                 if ((c>=48)&&(c<=57))
                 { sndx(c); sndcr(); y=c-48; if (y==0) y=10;}
               }
               switch(c)
               { case 'A':z=z+y; if (z>=ln) z=ln-1;
                          break;
                 case 'B':z=z-y; if (z<4) z=4;
                          break;
                 case 'C':sndx('>'); rinput(&msbuf[z][0]);
                          break;
                 case 'I':if (ln==50) rprint("No buffer space");
                          else {ln++; for (c=ln-1; c>z; c--)
                                       strcpy(&msbuf[c][0],&msbuf[c-1][0]);
                                sndx('>'); rinput(&msbuf[z][0]);
                               }
                          break;
                 case 'D':rprint("Line deleted.");
                          if (ln>0)
                          for (c=z; c<ln-1; c++)
                           strcpy(&msbuf[c][0],&msbuf[c+1][0]);
                          ln--; break;
}}}}         } }

getnum()
{/*accept mnum from user*/
int a;
char tmp[80];
sndx('>');
rinput(tmp);
tmp[3]=0;
strcpy(mnum,tmp);
zerofl=0;
if (mnum[0]==0) {strcpy(mnum,"000"); zerofl=1;}
if (mnum[1]==0) {mnum[2]=mnum[0]; mnum[0]='0'; mnum[1]='0';}
if (mnum[2]==0) {mnum[2]=mnum[1]; mnum[1]=mnum[0]; mnum[0]='0';}
for (a=0; a<3; a++)
 if ((mnum[a]>'9')||(mnum[a]<'0')) mnum[a]='0';
mnum[3]=0;
}

disply()
{/*show message mnum*/
char from[81],to[81],tmp[4];
strcpy(as,dos);
strcat(as,mnum);
unit=fopen(as,"r");
if (unit==0) {rprint("No such message!"); c='Q';}
else
{ crlf=0;
  rprint("Message #");
  crlf=1;
  rprint(mnum);
  sndcr();
  trdnum[0]=0;
  fgets(to,80,unit);
  if ((strcmp(sl,"SYSOP")==0)&&(to[3]=='!')) to[3]='*';
  strcpy(as,"From:"); strcat(as,name);
  if (((to[3]=='!')&&((index(to,name)!=5)||(to[strlen(name)+4]!=0)))
     &&(strcmp(as,name)!=0))
  { rprint("Private message");
    c='N';
    fclose(unit);
    strcpy(tmp,mnum);
    if ((strcmp(fm,oldm)>0)&&(strcmp(tmp,fm)<0)&&(strcmp(lm,oldm)>0))
      tmp[0]=tmp[0]+10;
    if ((strcmp(lm,fm)<0)&&(strcmp(lm,oldm)<0)&&(strcmp(tmp,fm)>0))
      tmp[0]=tmp[0]-10;
    if (strcmp(tmp,lm)>0) strcpy(lm,mnum);
  }
  else
 {if (to[3]=='*') to[3]='!';
  rprint(to);
  fgets(from,80,unit);
  rprint(from);
  while ((!feof(unit))&&(outflg))
  { fgets(bs,80,unit);
    rprint(bs);
    if ((trdnum[0]==0)&&(index(bs,"Reply to")==1))
    { trdnum[0]=bs[9];
      trdnum[1]=bs[10];
      trdnum[2]=bs[11];
      trdnum[3]=0;
    }
  }
  if (outflg==0) rprint("***Aborted***");
  fclose(unit);
  strcpy(tmp,mnum);
  if ((strcmp(fm,oldm)>0)&&(strcmp(tmp,fm)<0)&&(strcmp(lm,oldm)>0))
    tmp[0]=tmp[0]+10;
  if ((strcmp(lm,fm)<0)&&(strcmp(lm,oldm)<0)&&(strcmp(tmp,fm)>0))
    tmp[0]=tmp[0]-10;
  if (strcmp(tmp,lm)>0) strcpy(lm,mnum);
  c=0;
  if (thred==0)
  while (pos(c,"ANTRQ")==0)
  { rprint("[a]gain, [N]ext, [t]hread, [r]eply, [q]uit");
    c=waitx();
    if (c>96) c=c-32;
    if (c==13) c='N';
  }
  switch (c)
  {case 'A':rprint("Again..."); break;
   case 'N':rprint("Next..."); break;
   case 'T':thread(); break;
   case 'R':rprint("Reply..."); break;
   case 'Q':rprint("Quit..."); break;
  }
  if (c=='R')
  { strcpy(as,dos);
    strcat(as,oldm);
    unit=fopen(as,"w");
    strcpy(as,"TO:");
    if (to[3]=='!') strcat(as,"!");
    c=5;
    while (from[c])
      from[c-5]=from[c++];
    from[c-5]=0;
    strcat(as,from);
    rprint(as);
    if (unit) {c='R'; enter2();}
  }}
}}

thread()
{/*thread back a message*/
thred=1;
strcpy(svmnum,mnum);
while (thred)
{ if (trdnum[0]==0) {rprint("Not a reply..."); thred=0;}
 if (thred)
 {strcpy(mnum,trdnum);
  rprint("Threading...");
  disply();
  if (c!='Q') c=0;
  while ((c!='T')&&(c!='Q'))
  {rprint("[t]hread, [Q]uit");
   c=waitx();
   if (c>96) c=c-32;
   if (c==13) c='Q';
  }
  if (c=='Q') thred=0;
 }
}
rprint("Returning to original message...");
strcpy(mnum,svmnum);
disply();
}

getpre()
{ /*save oldm,fm, lm...read DOS and BASEN with BASE*/
/*load MAXMSG */
int z;
char ds1[80],ds2[10];
if (dos[0]!='!')
{ z=obase*3;
  fm2[z]=fm[0]; fm2[z+1]=fm[1]; fm2[z+2]=fm[2];
  lm2[z]=lm[0]; lm2[z+1]=lm[1]; lm2[z+2]=lm[2];
  oldm2[z]=oldm[0]; oldm2[z+1]=oldm[1]; oldm2[z+2]=oldm[2];
}
unit=fopen("DSK5.CONFIG","r");
if (unit) {
fgets(as,1,unit);
fgets(as,1,unit);
z=base+1;
while (z--)
{ fgets(ds1,80,unit);
  fgets(ds2,10,unit);
}
fclose(unit); }
z=base*3;
if (lm2[z]=='*') {rprint("You do not have access to that base.");
                  base=obase; z=base*3;
                 }
            else {strcpy(basen,ds1);
                  strcpy(dos,ds2);
                 }
fm[0]=fm2[z]; fm[1]=fm2[z+1]; fm[2]=fm2[z+2]; fm[3]=0;
lm[0]=lm2[z]; lm[1]=lm2[z+1]; lm[2]=lm2[z+2]; lm[3]=0;
oldm[0]=oldm2[z]; oldm[1]=oldm2[z+1]; oldm[2]=oldm2[z+2]; oldm[3]=0;
maxmsg=(basen[5]-48)*100+(basen[6]-48)*10+(basen[7]-48);
obase=base;
}

#include "dsk1.message2"
