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
