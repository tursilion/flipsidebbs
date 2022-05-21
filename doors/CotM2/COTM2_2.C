/*cotm2/c2*/

conv(as) char as[];
{/*string to number*/
int x;
as[3]=0;
if (as[0]==0) strcpy(as,"000");
if (as[1]==0) {as[2]=as[0]; as[1]='0'; as[0]='0';}
if (as[2]==0) {as[2]=as[1]; as[1]=as[0]; as[0]='0';}
x=(as[0]-48)*100+(as[1]-48)*10+as[2]-48;
return (x);
}

store()
{ int c;
  char d;
  rprint("You have found a store! Buy something? (y/n)");
  rinput(as);
  if (as[0]>95) as[0]=as[0]-32;
  d=as[0];
  while (d=='Y')
  { crlf=0;
    rprint("You have:");
    nputs(gold,4);
    rprint("1-life potion ");
    nputs((lev+1)*100,4);
    rprint("2-powerful sword ");
    nputs((lev+1)*150,4);
    rprint("3-train you ");
    nputs((lev+1)*200,4);
    rprint("4-HURT spell ");
    nputs((lev+1)*300,4);
    rprint("5-SHIELD spell ");
    nputs((lev+1)*300,4);
    rprint("6-HEAL spell ");
    nputs((lev+1)*300,4);
    crlf=1;
    rprint("0-nothing");
    c=0;
    while ((c<48)||(c>54))
      c=waitx();
    switch (c)
    { case '0':d=0; break;
      case '1':buy(100,&li,10); break;
      case '2':buy(150,&st,5); break;
      case '3':buy(200,&sk,10); break;
      case '4':buy(300,&p[0],1); break;
      case '5':buy(300,&p[1],1); break;
      case '6':buy(300,&p[2],1); break;
    }
   }
}

buy(a,b,c) int a,*b,c;
{ int d;
 d=(lev+1)*a;
 if (gold>=d) { rprint("Purchased.");
                gold=gold-d;
                if (c!=1)
                 *b=*b+(rnd((lev+1)*c)+c);
                else *b=*b+1; }
 else rprint("You don't have enough gold.");
}

up()
{
 rprint("Stairs going up one level! Use them? (y/n)");
 rinput(as);
 if (as[0]>95) as[0]=as[0]-32;
 if (as[0]=='Y') {rprint("Ok...going up!");
                  lev--; ldlvl(); }
}

down()
{rprint("Stairs going down one level! Use them? (y/n)");
rinput(as);
if ((as[0]=='Y')||(as[0]=='y'))
  { rprint("Down into the dangerous dungeon...");
    lev++; ldlvl(); }
}

trap()
{ rprint("A trap door opens!!!");
  rprint("Ahhhhhhhh! You fall down one level!!");
  strcpy(bn,"carelessness.");
  lev++; li=li-rnd(20); if (li<1) dead();
  ldlvl();
}

boss()
{ rprint("There is something odd about this place...");
  unit=fopen("DSK5.BOSS","r");
  if (unit==0) {rprint("disk error...");
                strcpy(as,"DSK5.FLP");
                ea5ld(); }
  fgets(bn,31,unit);
  fgets(bd,80,unit);
  fgets(as,80,unit);
  fclose(unit);
  eli=conv(&as[6]);
  as[6]=0;
  esk=conv(&as[3]);
  as[3]=0;
  est=conv(as);
  crlf=0;
  rprint("Suddenly, you are attacked by ");
  crlf=1;
  rprint(bn);
  rprint(bd);
  crlf=1;
  rprint("You must battle to the death! There is");
  rprint("no escape!");
  escp=0;
  fight();
  if (li>0)
 {sndcr();
  rprint("You have triumphed!!!!!");
  rprint("Congradulations!! You are now the");
  rprint("Creature of the Maze!!");
  rprint("Please enter a 1-line description to be saved");
  rprint("with your character.");
  rprint("(for example, the current description is:");
  crlf=0;
  rprint(bd);
  crlf=1;
  rprint(")");
  sndx('>');
  rinput(bd);
  if (li<100) li=li*10;
  if (li>999) li=999;
  if (sk>999) sk=999;
  if (st>999) st=999;
  rprint("saving...");
  unit=fopen("DSK5.BOSS","w");
  fputs(al,unit);
  fputs(bd,unit);
  nmake(st,3);
  strcpy(bn,as);
  nmake(sk,3);
  strcat(bn,as);
  nmake(li,3);
  strcat(bn,as);
  fputs(bn,unit);
  fclose(unit);
  rprint("Now I have to kill your original character...");
  strcpy(bn,"VICTORY!");
  dead();
}}

pcheck()
{ a=0;
  while (file[a][0])
  {if (pn!=a)
    if (file[a+2][0]==lev+48)
     if (file[a+2][1]==x+48)
      if (file[a+2][2]==y+48)
       if ((file[a+2][19]!=48)||(file[a+2][20]!=48)||(file[a+2][21]!=48))
      { rprint(&file[a+1][0]);
        rprint("is here! Fight? y/N");
        rinput(as);
        if ((as[0]=='Y')||(as[0]=='y'))
        { strcpy(bn,&file[a+1][0]);
          esk=(file[a+2][10]-48)*100+(file[a+2][11]-48)*10+file[a+2][12]-48;
          est=(file[a+2][13]-48)*100+(file[a+2][14]-48)*10+file[a+2][15]-48;
          eli=(file[a+2][19]-48)*100+(file[a+2][20]-48)*10+file[a+2][21]-48;
          escp=1;
          fight();
          if (eli<1)
          { strcpy(&file[a+2][19],"000");
            strcpy(&file[a+1][0],al);
            rprint("You get his gold!");
            gold=gold+(file[a+3][0]-48)*1000+(file[a+3][1]-48)*100
            +(file[a+3][2]-48)*10+file[a+3][3]-48;
          }
        }
      }
   a=a+4;
   }
}

fight()
{ int c;
c=0;
rprint("The battle commences!");
while ((li>0)&&(eli>0)&&(c!='E'))
{ rprint("You: Life Skill Strgth  Enemy: Life Skill Strgth");
  crlf=0;
  rprint("     ");
  nmake(li,3); rprint(as);
  rprint("  ");
  nmake(sk,3); rprint(as);
  rprint("   ");
  nmake(st,3); rprint(as);
  rprint("            ");
  nmake(eli,3); rprint(as);
  rprint("  ");
  nmake(esk,3); rprint(as);
  rprint("   ");
  nmake(est,3); rprint(as);
  crlf=1; sndcr();
  if (c!='C')
  { rprint("[A,C,M,E,?]");
    c=0;
    while (!pos("ACME",c))
    { c=waitx(); if (c>96) c=c-32;
      if (c=='?')
      { rprint("(A)ttack");
        rprint("(C)ontinuous (NO escape)");
        rprint("(M)agic");
        rprint("(E)scape");
      }
    }
    sndx(c); sndcr();
  }
  switch(c)
  {case 'E': if ((rnd(12)<rnd(12))&&(escp)) {rprint("You escaped!!");
                              return(0); }
             else {rprint("You didn't escape!"); c=0;}
             break;
   case 'M':magic(); break;
   case 'A':
   case 'C': rprint("You attack...");
             if (rnd((lev+1)*sk)>rnd((lev+1)*esk))
             {rprint("You hit it!!");
              eli=eli-rnd(st);}
             else rprint("You missed.");
             break;
  }
  if (eli>0)
  {rprint("Enemy attacks!");
  if (rnd((lev+1)*esk)>rnd((lev+1)*sk))
  { rprint("You are hit!!");
    if (shield) {rprint("SHIELD protects you!"); shield--;}
    else li=li-rnd(est);
  }
  else rprint("You avoid the attack.");
  }}
 if (li<1) {rprint("You have been killed."); dead();}
 else {rprint("You win!! Power's up!");
       st=st+rnd(est/3+1); sk=sk+rnd(esk/3+1);
      }
}

dead()
{/*aw...too bad*/
sndcr(); sndx(7);
rprint("Time to visit the big dungeon in the sky...");
rprint("Your adventure is over.");
rprint("Thanks for playing.");
strcpy(&file[pn+1][0],bn);
li=0;
m=0;
}

magic()
{/*do magic spell*/
int c;
crlf=0;
rprint("1-Hurt:");
sndx(p[0]+48); sndcr();
rprint("2-Shield:");
sndx(p[1]+48); sndcr();
rprint("3-Heal:");
sndx(p[2]+48); sndcr();
crlf=1;
rprint("0-cancel");
c=0;
while ((c<48)||(c>51))
 c=waitx();
if (c!=48)
{ if (p[c-49]) {p[c-49]--;
  switch(c)
  { case '1':rprint("HURT spell blasts out!!");
             eli=eli-10-rnd(120); break;
    case '2':rprint("SHIELD spell activated.");
             shield=5; break;
    case '3':rprint("HEAL spell activated");
             li=li+50+rnd(150); break;
  }}
  else rprint("You don't have any!!");
  }
else rprint("No spell used.");
}
