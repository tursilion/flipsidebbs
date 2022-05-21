/*
** c99 random number functions
**
** by Clint Pulley, based on TI-FORTH
** last edit 85/11/16 0810
*/
/*
** initialize the random seed
*/
randomize()
{
#asm
 MOVB @>8802,0  RESET VDPSTA
 CLR  1
R#1
 INC  1         COUNT
 MOVB @>8802,0  READ VDPSTA
 ANDI 0,>8000
 JEQ  R#1       IF NOT VDP INT
 MOV  1,@>83C0  STORE SEED
#endasm
}
/* generate a 16-bit random number
*/
rndnum()
{
#asm
 MOV  @>83C0,0  GET SEED
 MPY  @R#C1,0
 A    @R#C2,1
 SRC  1,5
 MOV  1,8       RETURN NUMBER
 MOV  1,@>83C0  NEXT SEED
#endasm
}
#asm
R#C1  DATA >6FE5
R#C2  DATA >7AB9
#endasm
/* generate a random number between
** 0 and n-1
*/
rnd(n) int n;
{
#asm
 BL   *12      CALL rndnum
 DATA RNDNUM
 ABS  8
 CLR  7
 MOV  @2(14),9 GET n
 DIV  9,7      REMAINDER IN R8
#endasm
}

int count,bang,name[80];

#include "dsk2.stdio"
#include "dsk1.fliputils"
#include "dsk1.stringfns"

/*russian roulette on the Flip Side!*/

main()
{ unit=fopen("DSK5.ONLINE","r");
  if (unit)
  { fgets(name,80,unit);
    fclose(unit); }
  else rego();
  count=0; randomize();
  rprint("Welcome to Russian Roulette, comrade.");
  rprint("(version 1.2)");
  sndcr();
  rprint("Instructions? (y/n)");
  rinput(as);
  if ((as[0]=='Y')||(as[0]=='y'))
  {rprint("Here you will gamble with your connection");
   rprint("with a loaded pistol. The pistol has four");
   rprint("chambers and 1 bullet. You will pull the");
   rprint("trigger by pressing enter. If the trigger");
   rprint("goes off...you will be disconnected.");
   rprint("If you pull the trigger 10 times (without");
   rprint("being killed) you will win the game!");
   rprint("(and get some extra credits!)");
   rprint("NOTE: the chamber is spun between each pull");
   rprint("if you don't want to pull the trigger");
   rprint("(i.e. chicken out) type 'a' for abort and");
   rprint("press enter.");
  }
  sndcr();
  bang=rnd(4);
  while (count<10)
  { crlf=0;
    rprint("Pull #");
    sndx(count+48);
    sndcr();
    rprint("Press enter <a=abort>:");
    crlf=1;
    rinput(as);
    if ((as[0]==65)||(as[0]==97)) count=99;
    if (rnd(4)==bang)
    { sndx(7); sndx(7); sndx(7);
      rprint("!!!!! >>> --- BANG --- <<< !!!");
      sndcr(); sndcr();
      rprint("LOSER!! LOSER!! LOSER!! LOSER!! LOSER!! LOSER!!");
      rprint("(you are dead! Call again!)");
      rego();
    }
    else
    { if (count!=99) {rprint(">!CLICK!<");
      count++;}
    }
  }
  if (count==99) { rprint("!!!CHICKEN!!! !!!CHICKEN!!! !!!CHICKEN!!!"); }
  if (count<99) { rprint("CONGRATULATIONS!! You have SURVIVED 5 pulls");
                  rprint("of the trigger!! <big deal>");
                  unit=fopen("DSK5.CREDS","r");
                  if (unit) {fgets(as,3,unit);
                             fclose(unit);
                             as[0]=as[0]+3;
                             unit=fopen("DSK5.CREDS","w");
                             fputs(as,unit);
                             fclose(unit);
                            }
                }
  rprint("Returning to online menu...");
  strcpy(as,"DSK5.DOR");
  ea5ld();
}
