/*online door selection menu for The Flip Side!*/

char name[81];
int c,q,creds;

#include "dsk2.stdio"
#include "dsk1.stringfns"
#include "dsk1.fliputils"

main()
{
while (1)
{ rprint("Flip Side Online Menu");
  rprint("---------------------");
  unit=fopen("DSK5.ONLINE","r");
  if (unit) {fgets(name,80,unit);
             fclose(unit); }
  unit=fopen("DSK5.ONLINLIST","r");
  q=65; crlf=0;
  if (unit)
  { while (!feof(unit))
    { fgets(as,80,unit);
      sndx(q++); sndx('=');
      rprint(as);
      sndcr();
      fgets(as,80,unit);
    }
    fclose(unit); crlf=1;
  }
  rprint("0 - return to main menu");
  sndcr();
  unit=fopen("DSK5.CREDS","r");
  if (unit==0) creds=1;
  else {fgets(as,2,unit);
        fclose(unit);
        creds=as[0]-48; }
  crlf=0;
  rprint("You have ");
  sndx(creds+48);
  crlf=1;
  rprint(" online credits.");
  sndcr();
  c=0;
  if (creds<1) {rprint("You are out of online credits.");
                c=48; }
  while (((c>=q)||(c<65))&&(c!=48))
  { c=waitx(); if (c>96) c=c-32; }
  if (c==48)
  { rprint("Returning to main..");
    strcpy(as,"DSK5.FLP");
    ea5ld();
  }
  sndx(c);
  sndcr();
  rprint("One moment...");
  creds--;
  unit=fopen("DSK5.CREDS","w");
  as[0]=creds+48;
  as[1]=0;
  fputs(as,unit);
  fclose(unit);
  c=c-64;
  unit=fopen("DSK5.ONLINLIST","r");
  if (unit==0) rprint("Unable to access files.");
  if (unit)
  { while (c)
    { fgets(as,80,unit);
      fgets(as,80,unit);
      c--;
    }
    fclose(unit);
    ea5ld();
  }
}}
