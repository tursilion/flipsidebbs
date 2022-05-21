/* Sysop Menu for The Flip Side v1.0*/                                          
                                                                                
int m,unum;                                                                     
                                                                                
char pw[81],name[81],c,k,sl[15],hl[10],lm[80];                                  
                                                                                
#include "dsk5.stdio"                                                           
#include "dsk1.fliputils"                                                       
#include "dsk1.stringfns"                                                       
                                                                                
main()                                                                          
{/*sysop menu*/                                                                 
unit=fopen("DSK5.ONLINE","r");                                                  
if (unit==0) {rprint("no ONLINE file! Hang up..."); rego();}                    
fgets(name,80,unit);                                                            
fclose(unit);                                                                   
m=1;                                                                            
while (m)                                                                       
 menu();                                                                        
strcpy(as,"DSK5.FLP");                                                          
ea5ld();                                                                        
}                                                                               
                                                                                
menu()                                                                          
{/*menu routine*/                                                               
int c;                                                                          
rprint("Flip Side: Sysop");                                                     
rprint("----------------");                                                     
rprint("1 - view/modify user stats");                                           
rprint("2 - view user list");                                                   
rprint("3 - read feedback");                                                    
rprint("4 - add login bulletin");                                               
rprint("5 - set message date");                                                 
rprint("6 - add user");                                                         
rprint("0 - exit to main");                                                     
sndcr();                                                                        
rprint("(1-5,0):");                                                             
c=0;                                                                            
while ((c<48)||(c>53))                                                          
 c=waitx();                                                                     
switch(c)                                                                       
{ case 48:strcpy(as,"DSK5.FLP");                                                
          ea5ld();                                                              
          break;                                                                
  case 49:modify();                                                             
          break;                                                                
  case 50:list();                                                               
          break;                                                                
  case 51:read();                                                               
          break;                                                                
  case 52:bullet();                                                             
          break;                                                                
  case 53:date();                                                               
          break;                                                                
  case 54:addusr();                                                             
          break;                                                                
}}                                                                              
                                                                                
list()                                                                          
{ int unum;                                                                     
char bs[3];                                                                     
unum=0;                                                                         
sndcr(); sndcr();                                                               
rprint("Flip Side user list");                                                  
rprint("-------------------");                                                  
sndcr();                                                                        
rprint("#    Name");                                                            
sndcr();                                                                        
unit=fopen("DSK5.USERS","r");                                                   
if (unit==0) rprint("error opening user file!");                                
crlf=0;                                                                         
if (unit)                                                                       
{ while (!feof(unit))                                                           
  { fgets(as,80,unit);                                                          
    bs[0]=unum/10+48;                                                           
    bs[1]=(unum%10)+48;                                                         
    bs[2]=0;                                                                    
    rprint(bs);                                                                 
    rprint("   ");                                                              
    rprint(as);                                                                 
    sndcr();                                                                    
    unum++;                                                                     
  }                                                                             
} crlf=1;                                                                       
  fclose(unit);                                                                 
}                                                                               
                                                                                
read()                                                                          
{/*read feedback*/                                                              
sndcr(); sndcr();                                                               
rprint("Feedback to Sysop");                                                    
rprint("-----------------");                                                    
unit=fopen("DSK5.FEEDBACK","r");                                                
if (unit)                                                                       
{ while (!feof(unit))                                                           
  { fgets(as,80,unit);                                                          
    rprint(as);                                                                 
}  fclose(unit);                                                                
}}                                                                              
                                                                                
modify()                                                                        
{ char bs[81];                                                                  
int unum,tar,cn;                                                                
sndcr(); sndcr();                                                               
rprint("Enter user name to modify");                                            
rinput(as);                                                                     
upper(as);                                                                      
unum=-1;                                                                        
unit=fopen("DSK5.USERS","r");                                                   
if (unit==0) rprint("USERS file error");                                        
if (unit)                                                                       
{ while ((strcmp(as,bs))&&(!feof(unit)))                                        
  { fgets(bs,80,unit); unum++; }                                                
  fclose(unit);                                                                 
if (!strcmp(as,bs))                                                             
{ crlf=0;                                                                       
  rprint("User name:");                                                         
  crlf=1;                                                                       
  rprint(as);                                                                   
  bs[0]=unum/10+48;                                                             
  bs[1]=unum%10+48;                                                             
  bs[2]=0;                                                                      
  strcpy(as,"User #");                                                          
  strcat(as,bs);                                                                
  rprint(as);                                                                   
  strcpy(as,"DSK5.USER");                                                       
  strcat(as,bs);                                                                
  unit=fopen(as,"r");                                                           
  if (unit==0) rprint("USER file error!!");                                     
  if (unit)                                                                     
  { fgets(pw,80,unit);                                                          
    fgets(sl,15,unit);                                                          
    fgets(hl,10,unit);                                                          
    fgets(lm,80,unit);                                                          
    fclose(unit);                                                               
    crlf=0;                                                                     
    rprint("Password:");                                                        
    rprint(pw); sndcr();                                                        
    rprint("Security level:");                                                  
    crlf=1;                                                                     
    rprint(sl);                                                                 
    rprint("Message base access (*=banned):");                                  
    unit=fopen("dsk5.config","r");                                              
    if (unit==0) {rprint("Error!"); return(0);}                                 
    fgets(bs,2,unit); fgets(bs,2,unit);                                         
    cn=0;                                                                       
    while (!feof(unit))                                                         
    {fgets(bs,80,unit);                                                         
     if (lm[cn*3]=='*') sndx('*');                                              
                  else sndx(' ');                                               
     rprint(bs);                                                                
     fgets(bs,1,unit);                                                          
     cn++;                                                                      
    }                                                                           
    fclose(unit);                                                               
    sndcr();                                                                    
    rprint("Press P to change password");                                       
    rprint("Press S to change security level");                                 
    rprint("Press R to restrict a msg base");                                   
    rprint("Press C to clear a msg base");                                      
    rprint("Anything else to continue");                                        
    c=waitx(); if (c>96) c=c-32;                                                
    switch(c)                                                                   
    {case 'P':rprint("Enter new password.");                                    
             rinput(pw);                                                        
             upper(pw);                                                         
             break;                                                             
     case 'S':rprint("Press: 1 - Co-Sysop");                                    
             rprint("       2 - Normal");                                       
             rprint("       3 - Restricted");                                   
             rprint("(any other=no change");                                    
             c=waitx();                                                         
             switch(c)                                                          
             {case 49:strcpy(sl,"CO-SYSOP"); break;                             
              case 50:strcpy(sl,"NORMAL"); break;                               
              case 51:strcpy(sl,"RESTRICTED"); break;                           
             }                                                                  
             break;                                                             
     case 'R':crlf=0;                                                           
              rprint("Restrict which base? (A-");                               
              sndx(cn+64);                                                      
              crlf=1; rprint(")");                                              
              rprint("(Space to abort)");                                       
              c=get('A',cn+64);                                                 
              if (c!=32)                                                        
              { crlf=0; rprint("Base "); sndx(c); sndcr(); crlf=1;              
                c=(c-65)*3; lm[c]=42; lm[c+1]=42; lm[c+2]=42;                   
              } else rprint("No change.");                                      
              break;                                                            
     case 'C':crlf=0;                                                           
              rprint("Clear which base? (A-");                                  
              sndx(cn+64);                                                      
              crlf=1; rprint(")");                                              
              rprint("(Space to abort)");                                       
              c=get('A',cn+64);                                                 
              if (c!=32)                                                        
              { crlf=0; rprint("Base "); sndx(c); sndcr(); crlf=1;              
                c=(c-65)*3; lm[c]=48; lm[c+1]=48; lm[c+2]=48;                   
              } else rprint("No change.");                                      
    }                                                                           
    unit=fopen(as,"w");                                                         
    fputs(pw,unit);                                                             
    fputs(sl,unit);                                                             
    fputs(hl,unit);                                                             
    fputs(lm,unit);                                                             
    fclose(unit);                                                               
}}}}                                                                            
                                                                                
get(a,b) int a,b;                                                               
{ /*get a key between a and b*/                                                 
int x;                                                                          
x=0;                                                                            
while ((x>b)||(x<a))                                                            
{ x=waitx();                                                                    
  if (x>96) x=x-32;                                                             
}                                                                               
return(x);                                                                      
}                                                                               
                                                                                
bullet()                                                                        
{/*add a new log-in bulletin*/                                                  
unit=fopen("DSK5.LOGIN","a");                                                   
if (unit==0) rprint("Unable to append file...");                                
else                                                                            
{ fputs("-------------------------------------",unit);                          
  sndcr();                                                                      
  rprint("Enter the new bulletin now. Enter a blank line to save.");            
  as[1]=0;                                                                      
  while (strcmp(as,"/s"))                                                       
  { sndx(">");                                                                  
    rinput(as);                                                                 
    fputs(as,unit);                                                             
    if (as[0]==0) strcpy(as,"/s");                                              
  }                                                                             
  sndcr();                                                                      
  rprint("saving...");                                                          
  fclose(unit);                                                                 
}}                                                                              
                                                                                
date()                                                                          
{/*change the date used in the message base*/                                   
unit=fopen("DSK5.DATE","r");                                                    
if (unit==0) rprint("No date.");                                                
else                                                                            
{ fgets(as,80,unit);                                                            
  fclose(unit);                                                                 
  crlf=0;                                                                       
  rprint("Current date:");                                                      
  crlf=1;                                                                       
  rprint(as);                                                                   
}                                                                               
sndcr();                                                                        
rprint("Enter new date...any meaningful format.");                              
rinput(as);                                                                     
if (as[0]==0) rprint("No change.");                                             
else                                                                            
{ unit=fopen("DSK5.DATE","w");                                                  
  fputs(as,unit);                                                               
  fclose(unit);                                                                 
  rprint("Updated..");                                                          
}}                                                                              
                                                                                
addusr()                                                                        
{ char bs[81],nnm[81];                                                          
int unum,tar,cn;                                                                
sndcr(); sndcr();                                                               
rprint("Add new user? (y/N)");                                                  
rinput(as);                                                                     
upper(as);                                                                      
if (as[0]!='Y') exit(0);                                                        
unum=0;                                                                         
unit=fopen("DSK5.USERS","r");                                                   
if (unit==0) rprint("USERS file error");                                        
if (unit)                                                                       
{ while (!feof(unit))                                                           
  { fgets(bs,80,unit); unum++; }                                                
  fclose(unit);                                                                 
  bs[0]=unum/10+48;                                                             
  bs[1]=unum%10+48;                                                             
  bs[2]=0;                                                                      
  strcpy(as,"User #");                                                          
  strcat(as,bs);                                                                
  rprint(as);                                                                   
  /* pw,hl,sl,lm */                                                             
  rprint("Enter new user's name.");                                             
  rinput(nnm);                                                                  
  rprint("Enter password.");                                                    
  rinput(pw);                                                                   
  rprint("Saving new user...");                                                 
  unit=fopen("dsk5.config","r");                                                
  if (unit)                                                                     
  { fgets(as,unit); fgets(as,unit);                                             
    strcpy(lm,&as[2]);                                                          
    fclose(unit);                                                               
  }                                                                             
  strcpy(hl,"FULL 00N");                                                        
  strcpy(sl,"NORMAL");                                                          
  strcpy(as,"DSK5.USER");                                                       
  strcat(as,bs);                                                                
  unit=fopen(as,"w");                                                           
  if (unit)                                                                     
  { fputs(pw,unit);                                                             
    fputs(hl,unit);                                                             
    fputs(sl,unit);                                                             
    fputs(lm,unit);                                                             
    fclose(unit);                                                               
    unit=fopen("dsk5.users","a");                                               
    fputs(nnm,unit);                                                            
    unit=fclose(unit);                                                          
  }                                                                             
  if (unit==0) rprint("Can't add user!");                                       
}}                                                                              
