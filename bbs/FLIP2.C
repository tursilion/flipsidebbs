/* The FLIP! Side BBS source part 2/2
V1.1*/

msgbas()
{/*load the message processor*/
if (strcmp(sl,"RESTRICTED")==0) {rstrct(); return(0);}
rprint("Establishing telepathic links..");
strcpy(as,"DSK5.MSG");
ea5ld();
}

drload()
{/*load the door program*/
if (strcmp(sl,"RESTRICTED")==0) {rstrct(); return(0);}
rprint("Generating alternate realities...");
strcpy(as,"DSK5.DOR");
ea5ld();
}

feedbk()
{/*record user feedback*/
sndcr();
rprint("Send feedback to Flipper? [Y]/n");
c=0;
while ((c!=13)&&(c!=89)&&(c!=78)&&(c!=110)&&(c!=121))
 c=waitx();
if ((c!=78)&&(c!=110))
{ sndcr();
  unit=fopen("DSK5.FEEDBACK","a");
  if (unit==0) rprint("Cannot open feedback file");
  if (unit!=0)
  { fputs("Feedback from:",unit);
    fputs(name,unit);
    fputs("---------------------------",unit);
    rprint("Enter message. Enter a blank line to save it.");
    sndcr();
    as[0]=5;
    while (as[0])
    {rinput(as);
     fputs(as,unit);
    }
    c=fclose(unit);
    if (c==0) rprint("File error! Feedback NOT saved!");
    else rprint("I'll see that he reads it.");
  }
}
else rprint("Fine! DON'T talk to me. <sulk>");
}

sysld()
{/*load sysop menu*/
if (index(sl,"SYS")==0)
  rprint("I told you, it's SECRET!!!");
else
{ rprint("Yeah, yeah. Just a minute...");
  strcpy(as,"DSK5.SYS");
  ea5ld();
}}

savusr()
{/*save the user file*/
char nstr[3];
in2str(unum,nstr);
strcpy(as,"DSK5.USER");
strcat(as,nstr);
unit=fopen(as,"w");
if (unit==0) {rprint("Unable to open user file! Fatal error!"); rego(); }
fputs(pw,unit);
fputs(sl,unit);
fputs(hl,unit);
fputs(lm,unit);
c=fclose(unit);
if (c==0) {rprint("Unable to save user file! Fatal error!"); rego();}
}

bullet()
{/*read log-in bulletin DSK5.LOGIN*/
unit=fopen("DSK5.LOGIN","r");
if (unit)
{ while ((!feof(unit))&&(outflg))
  { fgets(as,80,unit);
    rprint(as); }
  fclose(unit);
}
quest();
}

logsin()
{/*log a user sign-on in feedback*/
unit=fopen("DSK5.FEEDBACK","a");
if (unit)
{ strcpy(as,"*****User sign-on:");
  strcat(as,name);
  fputs(as,unit);
  fclose(unit);
}}

pinput(x) char x[];
{ /*input a password, secretly*/
char c;
int i;
c=0; i=0;
while ((c!=13)&&(i<75))
{ c=waitx();
  if (c>127) c=c-128;
  if ((c>31)&&(c<127))
    x[i++]=c;
  sndx('*');
}
sndcr();
x[i]=0;
}

quest()
{ /*check if user needs to do the questionaire
and do it, if need be*/
int c,unit2;
unit=fopen("dsk5.questlist","r");
if (unit==0) return(0);
c=0;
while (!feof(unit))
{ fgets(as,80,unit);
  if (strcmp(as,name)==0) c=1;
}
fclose(unit);
if (c) return(0);
rprint("Ah HA! YOU haven't filled out the new questionaire!");
sndcr();
unit2=fopen("dsk5.quests","r");
if (unit2) qpart2(unit2);
unit=fopen("dsk5.questlist","a");
fputs(name,unit);
fclose(unit);
}

nquest()
{/*new user questionairre*/
int unit2;
sndcr();
unit2=fopen("dsk5.nquest","r");
if (unit2) qpart2(unit2);
}

qpart2(unit2) int unit2;
{ /*questionaire part 2*/
char lm[4],bs[15],lm2[80],dos[10];
unit=fopen("dsk5.lastmess","r");
if (unit==0) return(0);
fgets(lm2,80,unit);
fclose(unit);
for (c=0; c<3; c++)
 lm[c]=lm2[c];
lm[3]=0;
unit=fopen("dsk5.config","r");
if (unit==0) return(0);
for (c=1; c<5; c++)
 fgets(dos,10,unit);
fclose(unit);
strcpy(bs,dos);
strcat(bs,lm);
unit=fopen(bs,"w");
fputs("***QUESTIONAIRE***",unit);
strcpy(as,"From:");
strcat(as,name);
fputs(as,unit);
strcpy(as," ");
fputs(as,unit);
while (!feof(unit2))
{ fgets(as,80,unit2);
  pose();
}
rprint("That's all...thanks...");
fclose(unit2);
fclose(unit);
lm[2]++;
if (lm[2]>'9')
{ lm[2]='0'; lm[1]++;
  if (lm[1]>'9')
  { lm[1]='0'; lm[0]++;
} }
lm2[0]=lm[0];
lm2[1]=lm[1];
lm2[2]=lm[2];
unit=fopen("dsk5.lastmess","w");
fputs(lm2,unit);
fclose(unit);
unit=fopen("dsk5.firstmess","r");
if (unit)
{ fgets(lm2,70,unit);
  fclose(unit);
  strcpy(as,dos);
  c=strlen(as)+3;
  strcat(as,lm2);
  as[c]=0;
  fdelete(as);
  lm2[2]++;
  if (lm2[2]>'9')
  { lm2[2]='0'; lm2[1]++;
    if (lm2[1]>'9')
    { lm2[1]='0'; lm2[0]++;
  } }
  unit=fopen("dsk5.firstmess","w");
  fputs(lm2,unit);
  fclose(unit);
}
}

pose()
{ /*ask as, get answer, put both into unit*/
int c;
char bs[80];
strcpy(bs,as);
fputs(bs,unit);
c=3;
while (c>0)
{rprint(bs);
 sndx('>');
 rinput(as);
 if ((as[0]==0)||(as[1]==0))
  switch(--c)
  { case 2: rprint("You MUST have more to say than that.");
            break;
    case 1: rprint("Elaborate a little...or else.");
            break;
  }
 else c=-5;
}
 if (c==0)
  { sndcr(); sndx(7);
    rprint("It's painfully obvious to me that you have no");
    rprint("intention of being a productive user. Thus, I");
    rprint("have no need for you here. Call back when you");
    rprint("learn to express yourself. Good bye.");
    rego();
  }
fputs(as,unit);
strcpy(as," ");
fputs(as,unit);
}

rstrct()
{/*inform user he's restricted access*/
sndcr(); sndx(7);
rprint("Sorry, you have RESTRICTED access and may not");
rprint("use that option. If you are not sure why you");
rprint("have RESTRICTED access, or wish to discuss it,");
rprint("leave feedback or page Flipper. Thanks.");
}
