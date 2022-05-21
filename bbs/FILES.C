/*file transfer subsection of The Flip Side!*/
/*based on PaulS Charleton's XMODEM routine for XB*/

#asm
       COPY "DSK1.XMODEM1"
#endasm

int send,check,error;
char name[81];

#include "dsk2.stdio"
#include "dsk1.stringfns"
#include "dsk1.fliputils"

xmodem()
{/*transfer file..name in as*/
#asm
      COPY "DSK1.XMODEM2"
#endasm
}

int a,b,c;

main()
{/*main routine for transfers*/
c=9;
while (c)
{ rprint("Flip Side file transfers");
  rprint("------------------------");
  rprint("1 - View file listing");
  rprint("2 - Upload a file");
  rprint("3 - Download a file");
  rprint("4 - see info about this area");
  rprint("0 - return to online menu");
  sndcr();
  c=waitx(); c=c-48;
  switch (c)
{ case 0: rprint("returning to online menu...");
          strcpy(as,"DSK5.DOR");
          ea5ld();
          break;
  case 1: sndcr(); sndcr();
          rprint("The following files are available for download");
          sndcr();
          unit=fopen("DSK5.FILES","r");
          if (unit==0) rprint("No files available.");
          else { while ((!feof(unit))&&(outflg))
                { fgets(as,80,unit);
                  rprint(as);
                }
                if (outflg==0) rprint("**Aborted**");
                fclose(unit);
               }
          sndcr();
          rprint("press a key...");
          waitx();
          break;
  case 2: upld();
          if (error) err();
          break;
  case 3: dnld();
          if (error) err();
          break;
  case 4: sndcr();
          unit=fopen("dsk5.fileinfo","r");
          while ((unit)&&(!feof(unit))&&(outflg))
          { fgets(as,80,unit); rprint(as); }
          fclose(unit);
          if (outflg==0) rprint("***Aborted***");
          else waitx();
          sndcr();
          break;
  }
}}

err()
{/*decipher ERROR*/
if (error<3) rprint("Unable to open file!!");
if (error==3) rprint("Too many errors!!");
if (error==4) rprint("Cancelled by user (that's you!!)");
if (error>4) rprint("Cancelled by Sysop (that's Flipper!!)");
}

upld()
{/*set up for upload*/
sndcr();
rprint("Enter name of file being uploaded.");
rprint("Must be 10 characters or less,");
rprint("no punctuation, including period.");
rprint("(ex: PIC/GIF instead of PIC.GIF)");
rinput(as);
upper(as);
if (as[0]!=0) {
if (strlen(as)>10) rprint("Filename too long!!");
else { rprint("Use CRC error checking? [Y]/n");
       b=waitx();
       if ((b=='n')||(b=='N')) {rprint("NO!"); check=-1;}
       else {rprint("Yup!"); check=0;}
       send=-1;
       sndcr();
       rprint("Ready to receive file. Control-x aborts.");
       xmodem();
}    }
}

dnld()
{/*set up for download*/
sndcr();
rprint("Enter name of file to download.");
rprint("Must be 10 characters or less,");
rprint("no punctuation, including period.");
rprint("(ex: PIC/GIF instead of PIC.GIF)");
rinput(as);
upper(as);
if (as[0]!=0) {
if (strlen(as)>10) rprint("Filename too long!!");
else { rprint("Use CRC error checking? [Y]/n");
       b=waitx();
       if ((b=='n')||(b=='N')) {rprint("NO!"); check=-1;}
       else {rprint("Yup!"); check=0;}
       send=0;
       sndcr();
       rprint("Ready to send file. Control-x aborts.");
       xmodem();
}    }
}
