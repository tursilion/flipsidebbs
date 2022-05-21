/* Tarot Reader for The Flip Side BBS */                                        
/* version 1.0 */                                                               
                                                                                
char cardn[40],cardm[160],cardmr[160];                                          
char name[80];                                                                  
int a,b,c,datapt;                                                               
int picked[11],cnum;                                                            
                                                                                
#include "dsk2.stdio"                                                           
#include "dsk1.fliputils"                                                       
#include "dsk1.stringfns"                                                       
#include "dsk5.random;c"                                                        
                                                                                
main()                                                                          
{ unit=fopen("DSK5.ONLINE","r");                                                
  if (unit==0) { strcpy(as,"DSK5.FLP");                                         
                 ea5ld(); }                                                     
  fgets(name,80,unit);                                                          
  fclose(unit);                                                                 
  strcpy(as,"Greetings, ");                                                     
  strcat(as,name);                                                              
  rprint(as);                                                                   
  sndcr();                                                                      
  rprint("I am Tee-Eye, the mystical sayer of sooth.");                         
  rprint("Would you like me to tell you what the cards have in");               
  rprint("store for you? (press Y or N)");                                      
  c=getyn();                                                                    
  if (c=='Y') docard();                                                         
  else { rprint("I am insulted!! Leave, then, and never again darken");         
         rprint("my door!");                                                    
       }                                                                        
  strcpy(as,"DSK5.DOR");                                                        
  ea5ld();                                                                      
}                                                                               
                                                                                
getyn()                                                                         
{ int c;                                                                        
  c=0;                                                                          
  while ((c!='Y')&&(c!='N'))                                                    
  { c=waitx(); if (c>90) c=c-32; }                                              
  return(c);                                                                    
}                                                                               
                                                                                
getkey()                                                                        
{ rprint("---Press a key---");                                                  
  waitx();                                                                      
}                                                                               
                                                                                
docard()                                                                        
{ sndcr();                                                                      
  rprint("Would you like a brief explanation? (Y/N)");                          
  c=getyn();                                                                    
  sndcr();                                                                      
  if (c=='Y')                                                                   
  { rprint("Tarot reading is an ancient art that goes back hundreds,");         
    rprint("if not thousands, of years. Tarot cards are brightly");             
    rprint("coloured cards, with divinitory meanings hidden in the");           
    rprint("pictures. The deck is similar to a regular playing deck,");         
    rprint("but larger. There are two parts, called 'Arcanas'. The");           
    rprint("'Major Arcana' contains the 'picture' cards. These cards");         
    rprint("are all independant of the others, and tend to have a");            
    rprint("more definite meaning attached. Examples are 'The Star',");         
    rprint("or the well-known 'Death'.");                                       
    rprint("The 'Minor Arcana' has four suits (Swords, Wands, Cups and");       
    rprint("Pentacles), each with 14 cards (Ace-10, Page, Knight, ");           
    rprint("Queen and King). The cards are layed out an interpreted");          
    rprint("by where and how they lay. This program will take care");           
    rprint("of interpretation for you.");                                       
    getkey();                                                                   
    sndcr();                                                                    
    rprint("A computer can only give general meanings. Not all the");           
    rprint("meanings given necessarily apply. You must decide for");            
    rprint("yourself what the cards are trying to tell you.");                  
    getkey();                                                                   
  }                                                                             
  random();                                                                     
  getsig();                                                                     
  sndcr();                                                                      
  rprint("Please enter your question, to better influence the cards.");         
  rinput(as);                                                                   
  c=0;                                                                          
  rprint("Shuffling...");                                                       
  while (as[c])                                                                 
  { while (as[c]--) rnd(5);                                                     
    c++;                                                                        
  }                                                                             
  sndcr();                                                                      
  readem();                                                                     
}                                                                               
                                                                                
get12(x) int x;                                                                 
{ int c;                                                                        
 c=0;                                                                           
 while ((c<'1')||(c>x+48))                                                      
   c=waitx();                                                                   
 return(c-48);                                                                  
}                                                                               
                                                                                
getsig()                                                                        
{ int a1,a2,a3;                                                                 
  sndcr();                                                                      
  rprint("First we must choose a significator, a card to represent you.");      
  rprint("Please answer these questions as honestly as possible.");             
  sndcr();                                                                      
  rprint("How old are you?");                                                   
  rprint("1: 16 or under");                                                     
  rprint("2: 17-25");                                                           
  rprint("3: over 25");                                                         
  a1=get12(3);                                                                  
  sndcr();                                                                      
  rprint("Are you:");                                                           
  rprint("1: male");                                                            
  rprint("2: female");                                                          
  a2=get12(2);                                                                  
  sndcr();                                                                      
  rprint("Are you:");                                                           
  rprint("1: neutral");                                                         
  rprint("2: easy-going");                                                      
  rprint("3: easily angered");                                                  
  rprint("4: a deep thinker");                                                  
  a3=get12(4);                                                                  
  sndcr();                                                                      
  picked[0]=(a3-1)*14;                                                          
  if (a1!=3) picked[0]=picked[0]+(4-a1);                                        
        else picked[0]=picked[0]+(a2-1);                                        
  picked[0]=picked[0]+22;                                                       
  read(picked[0]);                                                              
  sndcr();                                                                      
  crlf=0;                                                                       
  rprint("Your significator is ");                                              
  crlf=1;                                                                       
  rprint(cardn);                                                                
  sndcr();                                                                      
  cnum=1;                                                                       
}                                                                               
                                                                                
read(x) int x;                                                                  
{ int a;                                                                        
#asm                                                                            
 LI R0,CARDFS                                                                   
 MOV R0,@DATAPT                                                                 
#endasm                                                                         
 for (a=0; a<=x; a++)                                                           
#asm                                                                            
 MOV @DATAPT,R0                                                                 
 LI R1,CARDN                                                                    
LP1                                                                             
 CLR R2                                                                         
 MOVB *R0+,R2                                                                   
 CI R2,42*256                                                                   
 JEQ AHHA                                                                       
 MOVB R2,*R1+                                                                   
 JMP LP1                                                                        
AHHA                                                                            
 CLR R2                                                                         
 MOVB R2,*R1+                                                                   
 LI R1,CARDM                                                                    
LP2                                                                             
 CLR R2                                                                         
 MOVB *R0+,R2                                                                   
 CI R2,42*256                                                                   
 JEQ AHHA2                                                                      
 MOVB R2,*R1+                                                                   
 JMP LP2                                                                        
AHHA2                                                                           
 CLR R2                                                                         
 MOVB R2,*R1+                                                                   
 LI R1,CARDMR                                                                   
LP3                                                                             
 CLR R2                                                                         
 MOVB *R0+,R2                                                                   
 CI R2,42*256                                                                   
 JEQ AHHA3                                                                      
 MOVB R2,*R1+                                                                   
 JMP LP3                                                                        
AHHA3                                                                           
 CLR R2                                                                         
 MOVB R2,*R1+                                                                   
 MOV R0,@DATAPT                                                                 
#endasm                                                                         
}                                                                               
                                                                                
readem()                                                                        
{ sndcr();                                                                      
  rprint("This card crosses you.. it is your current main obstacle.");          
  read1();                                                                      
  rprint("This is beneath you.. it is your foundation in the matter.");         
  read1();                                                                      
  rprint("This is above you.. it is a goal of sorts.");                         
  read1();                                                                      
  rprint("This is behind you.. recent past events.");                           
  read1();                                                                      
  rprint("This is before you.. soon to occur.");                                
  read1();                                                                      
  rprint("This is your attitude/relationship to the matter.");                  
  read1();                                                                      
  rprint("This is your home environment, people and events around you.");       
  read1();                                                                      
  rprint("This card represents your hopes and fears.");                         
  read1();                                                                      
  rprint("This is the probable outcome, if nothing is changed.");               
  read1();                                                                      
  rprint("That is all. Thank you for visiting me...");                          
}                                                                               
                                                                                
read1()                                                                         
{ int x,y,fl,a;                                                                 
fl=1;                                                                           
while (fl)                                                                      
{ x=rnd(78); y=rnd(2);                                                          
  fl=0;                                                                         
  for (a=0; a<cnum; a++)                                                        
    if (picked[a]==x) fl=1;                                                     
}                                                                               
picked[cnum++]=x;                                                               
read(x);                                                                        
sndcr();                                                                        
rprint(cardn);                                                                  
if (y) {rprint("This card is reversed.");                                       
        rprint(cardmr); }                                                       
   else rprint(cardm);                                                          
sndcr();                                                                        
getkey();                                                                       
}                                                                               
                                                                                
#asm                                                                            
CARDFS TEXT 'The Magician*Skill, dimplomacy, '                                  
 TEXT 'self-confidence.*Disgrace, disquiet, inter'                              
 TEXT 'nal conflict.*'                                                          
 TEXT 'The High Priestess*Secrets, mystery, '                                   
 TEXT 'wisdom, science*Passion, ardour, conceit.*'                              
 TEXT 'The Empress*Fruitfulness, action, initiati'                              
 TEXT 've.*Light, truth'                                                        
 TEXT 'understanding, public rejoicing.*'                                       
 TEXT 'The Emperor*Stability, power, protection, '                              
 TEXT 'a great man.*'                                                           
 TEXT 'Benevolence, compassion, credit, immaturit'                              
 TEXT 'y.*'                                                                     
 TEXT 'The Hierophant*Captivity, servitude, a fat'                              
 TEXT 'her.*Society, '                                                          
 TEXT 'understanding, over-kindness, weakness.*'                                
 TEXT 'The Lovers*Attraction, love, beauty, trial'                              
 TEXT 's overcome.*'                                                            
 TEXT 'Failure, foolish plans.*'                                                
 TEXT 'The Chariot*Providence, triumph, vengence.'                              
 TEXT '*Riot, dispute, '                                                        
 TEXT 'litigation, defeat.*'                                                    
 TEXT 'Strength*Power, energy, courage.*Abuse of '                              
 TEXT 'power, weakness, '                                                       
 TEXT 'dischord.*'                                                              
 TEXT 'The Hermit*Prudence, treason, corruption.*'                              
 TEXT 'Concealment, disguise, fear, paranoia.*'                                 
 TEXT 'Wheel of Fortune*Destiny, good luck, succe'                              
 TEXT 'ss.*'                                                                    
 TEXT 'Abundance, bad luck, superfluity.*'                                      
 TEXT 'Justice*Equity, rightness, fairness.*Law, '                              
 TEXT 'bigotry, excessive '                                                     
 TEXT 'severity.*'                                                              
 TEXT 'The Hanged Man*Wisdom, trials, divination.'                              
 TEXT '*Selfishness, '                                                          
 TEXT 'peer pressure.*'                                                         
 TEXT 'Death*Change, new events replace old, end '                              
 TEXT 'of old ways.*'                                                           
 TEXT 'Inertia, stagnation, sleep.*'                                            
 TEXT 'Temperance*Economy, moderation, frugality,'                              
 TEXT ' accomodation.*'                                                         
 TEXT 'Religion, disunion, competing interests.*'                               
 TEXT 'The Devil*Violence, extraordinary efforts,'                              
 TEXT ' force, reluctance '                                                     
 TEXT 'to change.*Evilness, weakness, pettiness.*'                              
 TEXT 'The Tower*Misery, distress, violent change'                              
 TEXT ', disgrace.*'                                                            
 TEXT 'Oppression, imprisonment, tyranny.*'                                     
 TEXT 'The Star*Hope, bright prospects, knowledge'                              
 TEXT '.*Arrogance, '                                                           
 TEXT 'haughtiness, impotence.*'                                                
 TEXT 'The Moon*Hidden enemies, danger, darkness,'                              
 TEXT ' deception.*'                                                            
 TEXT 'Instability, inconsistency, some deception'                              
 TEXT '.*'                                                                      
 TEXT 'The Sun*Material happiness, marriage, cont'                              
 TEXT 'entment.*'                                                               
 TEXT 'Happiness, contentment.*'                                                
 TEXT 'Judgement*Change of position, renewal, rew'                              
 TEXT 'ard/punishment.*'                                                        
 TEXT 'Weakness, simplicity, deliberation.*'                                    
 TEXT 'The Fool*Folly, mania, intoxication, extra'                              
 TEXT 'vagance, an '                                                            
 TEXT 'important decision.*Negligence, absence, c'                              
 TEXT 'arelessness, vanity.*'                                                   
 TEXT 'The World*Success, a trip, a move.*Inertia'                              
 TEXT ', stagnation, '                                                          
 TEXT 'permanence.*'                                                            
 TEXT 'King of Wands*A dark, friendly man, honest'                              
 TEXT ' and conscientious.*'                                                    
 TEXT 'Good, yet severe, austere and tolerant.*'                                
 TEXT 'Queen of Wands*A dark, friendly woman, cha'                              
 TEXT 'ste, loving, honourab'                                                   
 TEXT 'le.*Jealousy, deceit, infidelity.*'                                      
 TEXT 'Knight of Wands*A friendly young man, depa'                              
 TEXT 'rture, absence, '                                                        
 TEXT 'moving.*Division, interruption, dischord.*'                              
 TEXT 'Page of Wands*A faithful young person, a l'                              
 TEXT 'over, an envoy, news.*'                                                  
 TEXT 'Announcements, bad news, indecision and in'                              
 TEXT 'stability.*'                                                             
 TEXT 'Ten of Wands*Opression, disguise, bad tidi'                              
 TEXT 'ngs, loss of a lawsuit.*'                                                
 TEXT 'Contrarities, difficulties, intrigues.*'                                 
 TEXT 'Nine of Wands*Strong defense, delay, expec'                              
 TEXT 'tation of a battle.*'                                                    
 TEXT 'Obstacles, adversity, calamity.*'                                        
 TEXT 'Eight of Wands*Activity, swiftness, hope, '                              
 TEXT 'love.*'                                                                  
 TEXT 'Jealousy, disputes, bad conscience, quarre'                              
 TEXT 'ls.*'                                                                    
 TEXT 'Seven of Wands*Valour, dicussion, negotiat'                              
 TEXT 'ions, success.*'                                                         
 TEXT 'Perplexity, embarrassment, anxiety.*'                                    
 TEXT 'Six of Wands*Victory, great news.*Apprehen'                              
 TEXT 'sion, treachery, '                                                       
 TEXT 'disloyalty, fear of loss.*'                                              
 TEXT 'Five of Wands*Imitation, the fight for mat'                              
 TEXT 'erial wealth.*'                                                          
 TEXT 'Litigation, disputes, trickery, contradict'                              
 TEXT 'ion.*'                                                                   
 TEXT 'Four of Wands*Harmony, prosperity, peace.*'                              
 TEXT 'Prosperity, peace, beauty, embellishment.*'                              
 TEXT 'Three of Wands*Established strength, comme'                              
 TEXT 'rce, trade, existing '                                                   
 TEXT 'success.*End of troubles, suspension of ad'                              
 TEXT 'versity, hard work.*'                                                    
 TEXT 'Two of Wands*Unhappiness despite material '                              
 TEXT 'success and wealth.*'                                                    
 TEXT 'Surprise, wonder, fear.*'                                                
 TEXT 'Ace of Wands*Creation, invention, a beginn'                              
 TEXT 'ing.*'                                                                   
 TEXT 'A fall from power, ruin, clouded joy.*'                                  
 TEXT 'King of Cups*A fair, responsible man, crea'                              
 TEXT 'tive intelligence.*'                                                     
 TEXT 'A dishonest, double-dealing man, injustice'                              
 TEXT ', vice, scandal.*'                                                       
 TEXT 'Queen of Cups*A good, honest, devoted woma'                              
 TEXT 'n, wisdom, virtue.*'                                                     
 TEXT 'Untrustworthy or perverse woman, dishonour'                              
 TEXT ', depravity.*'                                                           
 TEXT 'Knight of Cups*arrival of someone, maybe a'                              
 TEXT ' messenger, a '                                                          
 TEXT 'proposition or invitation.*Trickery, subtl'                              
 TEXT 'ety, fraud.*'                                                            
 TEXT 'Page of Cups*A studious youth, news, medit'                              
 TEXT 'ation, business.*'                                                       
 TEXT 'Attachment, deception.*'                                                 
 TEXT 'Ten of Cups*Contentment, perfect repose, c'                              
 TEXT 'lear conscience.*'                                                       
 TEXT 'False heart, bad conscience, violence.*'                                 
 TEXT 'Nine of Cups*Contentment, physical well-be'                              
 TEXT 'ing, victory, '                                                          
 TEXT 'satisfaction.*Loyalty, but including mista'                              
 TEXT 'kes or imperfections.*'                                                  
 TEXT 'Eight of Cups*Desertion of previous undert'                              
 TEXT 'akings.*'                                                                
 TEXT 'Great joy, happiness, feasting.*'                                        
 TEXT 'Seven of Cups*Division of concentration, t'                              
 TEXT 'oo many projects are '                                                   
 TEXT 'being undertaken at once.*Desire, will, de'                              
 TEXT 'termination, a '                                                         
 TEXT 'project.*'                                                               
 TEXT 'Six of Cups*Past happiness, memories.*The '                              
 TEXT 'future, renewal.*'                                                       
 TEXT 'Five of Cups*Loss, but something more rema'                              
 TEXT 'ins. Too much '                                                          
 TEXT 'concern over the loss while ignoring what '                              
 TEXT 'is left.*'                                                               
 TEXT 'News, alliances, flase projects.*'                                       
 TEXT 'Four of Cups*Weariness, disgust, dissatisf'                              
 TEXT 'action with all that '                                                   
 TEXT 'is offered.*Novelty, new relations, new in'                              
 TEXT 'structions.*'                                                            
 TEXT 'Three of Cups*Good conclusion of a matter,'                              
 TEXT ' victory, healing.*'                                                     
 TEXT 'Achievement, end.*'                                                      
 TEXT 'Two of Cups*Love, friendship, sympathy.*Fa'                              
 TEXT 'lse love, folly, '                                                       
 TEXT 'a misunderstanding.*'                                                    
 TEXT 'Ace of Cups*True joy, abundance, holiness.'                              
 TEXT '*False feelings, '                                                       
 TEXT 'instability, revolution.*'                                               
 TEXT 'King of Swords*Judgement, power, authority'                              
 TEXT ', law.*'                                                                 
 TEXT 'Cruelty, evil intentions.*'                                              
 TEXT 'Queen of Swords*Widowhood, absense, steril'                              
 TEXT 'ity, separation.*'                                                       
 TEXT 'Malice, bigotry, deceit.*'                                               
 TEXT 'Knight of Swords*Skill, bravery in defense'                              
 TEXT ' or offense.*'                                                           
 TEXT 'Incapacity, extravagance.*'                                              
 TEXT 'Page of Swords*Secrecy, spying, vigilance.'                              
 TEXT '*Unprepared state, '                                                     
 TEXT 'hostile spying.*'                                                        
 TEXT 'Ten of Swords*Pain, sadness, desolation, r'                              
 TEXT 'uthless enemy.*'                                                         
 TEXT 'Temporary advantage, profit, or power.*'                                 
 TEXT 'Nine of Swords*Death, failure, deception, '                              
 TEXT 'dispair.*'                                                               
 TEXT 'Imprisonment, suspicion, shame.*'                                        
 TEXT 'Eight of Swords*Bad news, conflict, sickne'                              
 TEXT 'ss.*Opposition, '                                                        
 TEXT 'accident, treachery, fatality.*'                                         
 TEXT 'Seven of Swords*Lack of guard. Severe weak'                              
 TEXT 'ening of battle '                                                        
 TEXT 'readiness.*Good advice, instruction.*'                                   
 TEXT 'Six of Swords*Journey by water, a route, c'                              
 TEXT 'ommissionary.*'                                                          
 TEXT 'Declaration, confession.*'                                               
 TEXT 'Five of Swords*Destruction, dishonour, los'                              
 TEXT 's.*Distruction, '                                                        
 TEXT 'dishonour, loss.*'                                                       
 TEXT 'Four of Swords*Vigilance, solitude, retrea'                              
 TEXT 't, exile.*'                                                              
 TEXT 'Circumspection, economy, precaution.*'                                   
 TEXT 'Three of Swords*Removal, absense, delay, d'                              
 TEXT 'ivision.*Error, '                                                        
 TEXT 'loss, distraction, confusion.*'                                          
 TEXT 'Two of Swords*Conformity, friendship, bala'                              
 TEXT 'nce of power.*'                                                          
 TEXT 'Imposture, falsehood, disloyalty.*'                                      
 TEXT 'Ace of Swords*Triumph, conquest, great for'                              
 TEXT 'ce.*Conquest, or '                                                       
 TEXT 'great force, with negative results.*'                                    
 TEXT 'King of Pentacles*Courage, lethargy, valou'                              
 TEXT 'r.*Vice, weak'                                                           
 TEXT 'ness, ugliness, corruption.*'                                            
 TEXT 'Queen of Pentacles*Generosity, magnificenc'                              
 TEXT 'e, liberty.*'                                                            
 TEXT 'Evil, suspicion, suspense, fear, mistrust.'                              
 TEXT '*'                                                                       
 TEXT 'Knight of Pentacles*Utility, interest, res'                              
 TEXT 'ponsibility.*'                                                           
 TEXT 'Inertia, discouragement, carelessness.*'                                 
 TEXT 'Page of Pentacles*Application, study, refl'                              
 TEXT 'ection.*'                                                                
 TEXT 'Prodigality, liberality, luxury.*'                                       
 TEXT 'Ten of Pentacles*Gain, riches, family matt'                              
 TEXT 'ers.*Chance, loss,'                                                      
 TEXT ' robbery.*'                                                              
 TEXT 'Nine of Pentacles*Prudence, safety, succes'                              
 TEXT 's, discernment.*'                                                        
 TEXT 'Roguery, deception, bad faith.*'                                         
 TEXT 'Eight of Pentacles*Employment, craftsmansh'                              
 TEXT 'ip, skill in business.*'                                                 
 TEXT 'Voided ambition, exaction.*'                                             
 TEXT 'Seven of Pentacles*Money, business, barter'                              
 TEXT '.*Anxiety about '                                                        
 TEXT 'money.*'                                                                 
 TEXT 'Six of Pentacles*Gifts, gratification, att'                              
 TEXT 'ention.*Desire, envy,'                                                   
 TEXT ' jealousy, illusion.*'                                                   
 TEXT 'Five of Pentacles*Material problems, desti'                              
 TEXT 'tution.*Disorder, '                                                      
 TEXT 'chaos, dischrord.*'                                                      
 TEXT 'Four of Pentacles*Surety of possessions, h'                              
 TEXT 'olding on to what '                                                      
 TEXT 'one has, gifts, legacy or inheritance.*Sus'                              
 TEXT 'pense, delay, '                                                          
 TEXT 'opposition.*'                                                            
 TEXT 'Three of Pentacles*Trade, skilled labour, '                              
 TEXT 'reknown, glory.*'                                                        
 TEXT 'Mediocrity, pettiness, weakness.*'                                       
 TEXT 'Two of Pentacles*Written messages, happine'                              
 TEXT 'ss.*'                                                                    
 TEXT 'Forced happiness, written exchange.*'                                    
 TEXT 'Ace of Pentacles*Perfect contentment, ecst'                              
 TEXT 'asy, intelligence, '                                                     
 TEXT 'wealth.*Evil side of wealth, bad intellige'                              
 TEXT 'nce.*'                                                                   
 TEXT '******'                                                                  
#endasm                                                                         
