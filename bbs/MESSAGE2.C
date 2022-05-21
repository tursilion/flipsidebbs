/*MESSAGE PROCESSOR V1.5 P2/2*/
select()
{/* choose a message base*/
int z,c;
char bs[80];
sndcr();
rprint("Flip Side message bases:");
rprint("------------------------");
unit=fopen("DSK5.CONFIG","r");
fgets(as,1,unit);
fgets(as,1,unit);
z=-1;
while (!feof(unit))
{ fgets(as,80,unit);
  fgets(bs,80,unit);
  rprint(as);
  z++;
}
fclose(unit);
sndcr();
crlf=0;
rprint("Which dimension? (A-");
sndx(z+65);
crlf=1;
rprint(")?");
c=0;
while ((c<65)||(c>z+65))
{ c=waitx(); if (c>96) c=c-32; }
sndx(c); sndcr();
base=c-65;
}

quick()
{/* do a newread quickscan through all bases*/
int qbn,z;
qbn=1;
while (qbn)
{crlf=0;
 rprint("Going to base ");
 sndx(64+qbn);
 sndcr(); crlf=1;
 base=qbn-1;
 getpre();
 ncount();
 newrd();
 unit=fopen("DSK5.CONFIG","r");
 fgets(as,1,unit);
 fgets(as,1,unit);
 z=0;
 while (!feof(unit))
 { fgets(as,1,unit);
   fgets(as,1,unit);
   z++;
 }
 fclose(unit);
 if (qbn==z) qbn=0;
        else qbn++;
}
sndcr();
rprint("Quickscan completed.");
}
