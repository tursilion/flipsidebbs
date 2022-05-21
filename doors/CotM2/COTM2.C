/*Creature of the Maze 2 */
/*for the Flip Side BBS*/

int lev,x,y,sk,st,li;
int gold,a,b,pn,turns,m;
int esk,est,eli,escp,bn[30];
int nth,sth,east,west;
int p[3],shield;
#asm
 AORG >2800
#endasm
char name[81],al[81],bd[80];
char file[101][31];
char level[10][11];
#asm
 RORG
#endasm

#include "dsk2.stdio"
#include "dsk1.fliputils"
#include "dsk1.stringfns"
#include "dsk1.random;c"

main()
{ unit=fopen("DSK5.ONLINE","r");
  if (unit==0) rego();
  fgets(name,80,unit);
  fclose(unit);
  rprint("Creature of the Maze 2!");
  rprint("loading stats...");
  random();
  for (a=0; a<101; a++)
    file[a][0]=0;
  unit=fopen("DSK5.COTM2DATA","r");
  a=0;
  while ((a<100)&&(!feof(unit)))
    fgets(&file[a++][0],30,unit);
  fclose(unit);
  pn=0;
  while ((pn<a)&&(strcmp(&file[pn][0],name)))
    pn=pn+4;
  if (pn>=a) newusr();
        else oldusr();
  if (li==0) {crlf=0;
              rprint("You were killed by ");
              crlf=1;
              rprint(al);
              rprint("Starting over...");
              a=pn;
              newusr(); }
  stats();
  ldlvl();
  m=1; shield=0;
  while ((m)&&(turns))
  { li=li+lev+1; if (li>999) li=999;
    play(); turns--;
    if (li>999) li=999;
    if (st>999) st=999;
    if (sk>999) sk=999;
  }
  sndcr();
  if (turns==0) rprint("You are out of turns!");
  savusr();
  rprint("returning to online menu...");
  strcpy(as,"DSK5.DOR");
  ea5ld();
}

nmake(x,l) int x,l;
{ /*# to string in as (1-5)*/
int y;
y=x/10000; x=x%10000;
if (l>=5) as[0]=y+48;
y=x/1000; x=x%1000;
if (l>=4) as[l-4]=y+48;
y=x/100; x=x%100;
if (l>=3) as[l-3]=y+48;
y=x/10; x=x%10;
if (l>=2) as[l-2]=y+48;
as[l-1]=x+48;
as[l]=0;
}

ldlvl()
{/*load level # lev*/
strcpy(as,"DSK5.LEVEL");
as[10]=lev+48; as[11]=0;
unit=fopen(as,"r");
if (unit==0) {rprint("error!!"); rego();}
for (a=0; a<10; a++)
 fgets(&level[a][0],11,unit);
fclose(unit);
}

conv2(as) char as[];
{ char bs[4];
  int a;
  for (a=0; a<4; a++)
    bs[a]=as[a];
  a=conv(bs);
  return(a);
}

oldusr()
{/*load an old users stats (#pn)*/
strcpy(name,&file[pn][0]);
strcpy(al,&file[pn+1][0]);
strcpy(as,&file[pn+2][0]);
lev=as[0]-48;
x=as[1]-48;
y=as[2]-48;
p[0]=as[3]-48;
p[1]=as[4]-48;
p[2]=as[5]-48;
sk=conv2(as+10);
st=conv2(as+13);
li=conv2(as+19);
strcpy(as,&file[pn+3][0]);
gold=(as[0]-48)*1000+(as[1]-48)*100+(as[2]-48)*10+as[3]-48;
turns=30;
}

newusr()
{/*create new user*/
char bs[81];
if (a>96) {rprint("Sorry, no room for more players.");
           rprint("Returning to BBS...");
           strcpy(as,"DSK5.FLP");
           ea5ld();
          }
rprint("You are a new player!");
rprint("Enter an alias to use with the game");
sndx('>');
rinput(al);
if (al[0]==0) strcpy(al,name);
al[30]=0;
rprint("One moment...creating character...");
pn=a;
strcpy(&file[pn][0],name);
strcpy(&file[pn+1][0],al);
strcpy(bs,"0000000000");
sk=rnd(15)+10; st=rnd(20)+5;
li=rnd(20)+15;
nmake(sk,3); strcat(bs,as);
nmake(st,3); strcat(bs,as);
strcpy(as,"000"); strcat(bs,as);
nmake(li,3); strcat(bs,as);
strcpy(&file[pn+2][0],bs);
strcpy(&file[pn+3][0],"000050");
oldusr();
}

stats()
{/*display player stats*/
sndcr();
crlf=0;
rprint("Info for ");
rprint(al);
sndcr(); sndcr();
rprint("Level:");
sndx(lev+48);
sndcr();
rprint("Location:(");
sndx(x+48);
sndx(',');
sndx(y+48);
sndx(')');
sndcr();
rprint("Life:");
nputs(li,3);
rprint("Skill:");
nputs(sk,3);
rprint("Strength:");
nputs(st,3);
rprint("Gold:");
nputs(gold,4);
rprint("Turns left:");
nputs(turns,2);
rprint("HURT spells:");
nputs(p[0],1);
rprint("SHIELD spells:");
nputs(p[1],1);
rprint("HEAL spells:");
nputs(p[2],1);
sndcr();
crlf=1;
}

nputs(a,b) int a,b;
{ nmake(a,b);
  rprint(as);
  sndcr();
}

savusr()
{ /*save user file*/
rprint("Saving...");
file[pn+2][0]=lev+48;
file[pn+2][1]=x+48;
file[pn+2][2]=y+48;
file[pn+2][3]=p[0]+48;
file[pn+2][4]=p[1]+48;
file[pn+2][5]=p[2]+48;
nmake(sk,3);
strcpy(&file[pn+2][10],as);
nmake(st,3);
strcpy(&file[pn+2][13],as);
strcpy(as,"000");
strcpy(&file[pn+2][16],as);
nmake(li,3);
strcpy(&file[pn+2][19],as);
nmake(gold,4);
strcpy(&file[pn+3][0],as);
unit=fopen("DSK5.COTM2DATA","w");
a=0;
while (file[a][0])
  fputs(&file[a++][0],unit);
fclose(unit);
}

pos(s,c) char s[],c;
{ int x;
x=0;
if (c>96) c=c-32;
while ((s[x]!=c)&&(s[x])) x++;
if (s[x]==0) x=0; else x++;
return(x);
}

play()
{/*one turn...*/
int c,d;
d=1;
while (d)
{ rprint("You can go:");
  crlf=0; nth=0; sth=0; east=0; west=0;
  if (y>0) if (level[y-1][x]!='#') {rprint("North "); nth=1;}
  if (y<9) if (level[y+1][x]!='#') {rprint("South "); sth=1;}
  if (x<9) if (level[y][x+1]!='#') {rprint("East "); east=1;}
  if (x>0) if (level[y][x-1]!='#') {rprint("West"); west=1;}
  sndcr();
  crlf=1;
  sndcr();
  rprint("[N,S,E,W,I,M,R,Q,?]");
  c=0;
  while (!pos("NSWEIMRQ?",c))
  { c=waitx(); if (c>96) c=c-32; }
  sndx(c);
  sndcr();
  switch (c)
{ case '?': rprint("(N)orth");
            rprint("(S)outh");
            rprint("(E)ast");
            rprint("(W)est");
            rprint("(I)nfo");
            rprint("(M)agic");
            rprint("(R)est");
            rprint("(Q)uit");
            break;
  case 'N': if ((y==0)||(nth==0))
              rprint("You cannot go that way.");
            else { y--; d=0; }
            break;
  case 'S': if ((y==9)||(sth==0))
              rprint("You cannot go that way.");
            else {y++; d=0;}
            break;
  case 'E': if ((x==9)||(east==0))
              rprint("You cannot go that way.");
            else {x++; d=0;}
            break;
  case 'W': if ((x==0)||(west==0))
              rprint("You cannot go that way.");
            else {x--; d=0;}
            break;
  case 'I': stats();
            break;
  case 'M': magic();
            break;
  case 'R': rprint("You rest...");
            li=li+rnd(10*(lev+1))+1;
            return(0);
            break;
  case 'Q': d=0; m=0; break;
  }
}
if (m) {
switch (level[y][x])
{ case 36: empty(); break;
  case 37: store(); break;
  case 38: up(); break;
  case 39: down(); break;
  case 43: trap(); break;
  case 46: boss(); break;
}
pcheck();
}}

empty()
{ a=rnd(35);
  if (a>30) {rprint("You find some gold!");
             gold=gold+rnd(200); a=0;}
  if ((a<20)||(a-20>lev)) rprint("There is nothing here.");
  else { a=a-20; crlf=0;
         rprint("You confront ");
     crlf=1;
switch(a)
{ case 1: strcpy(bn,"a zombie");
          esk=2; est=5; break;
  case 2: strcpy(bn,"an ogre");
          esk=3; est=8; break;
  case 3: strcpy(bn,"a vampire");
          esk=7; est=8; break;
  case 4: strcpy(bn,"a gremlin");
          esk=6; est=2; break;
  case 5: strcpy(bn,"a giant ant");
          esk=6; est=7; break;
  case 6: strcpy(bn,"a giant spider");
          esk=6; est=4; break;
  case 7: strcpy(bn,"a demon");
          esk=8; est=6; break;
  case 8: strcpy(bn,"a giant scorpion");
          esk=7; est=5; break;
  case 9: strcpy(bn,"a evil wizard");
          esk=9; est=8; break;
  default:strcpy(bn,"a slime mold");
          esk=3; est=4; break;
}
rprint(bn);
eli=rnd((lev+1)*30)+(lev+1)*20;
esk=(esk*eli)/7+1;
est=(est*esk)/7+1;
escp=1;
fight();
}}

#include "dsk1.cotm2_2.c"
