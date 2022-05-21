/*Flip Side Loader - front-door v1.0                                            
  no echo capability...yet*/                                                    
                                                                                
char name[81];                                                                  
#include "dsk2.stdio"                                                           
#include "dsk1.fliputils"                                                       
#include "dsk1.stringfns"                                                       
                                                                                
main()                                                                          
{ /*just gets the user up and going*/                                           
int c,z;                                                                        
char bs[80];                                                                    
#asm                                                                            
 LI R0,>0500                                                                    
 MOVB R0,@>8374 *SET KEYBOARD MODE                                              
#endasm                                                                         
puts("Flip Side Loader - Horizon boot routine v1.1\n");                         
puts("by Mike Ward\n");                                                         
unit=fopen("dsk5.config","r");                                                  
fclose(unit);                                                                   
unit=fopen("dsk5.config","r");                                                  
if (unit!=0)                                                                    
{                                                                               
fgets(bs,80,unit);                                                              
fclose(unit);                                                                   
crlf=0;                                                                         
init24();                                                                       
clrrs();                                                                        
sndx(13);                                                                       
if (bs[0]=='A')                                                                 
{rprint(bs);                                                                    
 sndx(13);                                                                      
 clrrs();                                                                       
 waitx();                                                                       
 clrrs();                                                                       
}                                                                               
crlf=1;                                                                         
}                                                                               
answer();                                                                       
if (index(as,"24")==0) {init12(); z=0;} else {init24(); z=1;}                   
c=0;                                                                            
while (c!=13)                                                                   
{rprint("REALITY.SYS corrupted. Press <return> to reboot universe.");           
c=waitx(); if (c>127) c=c-128;                                                  
if (c!=13)                                                                      
 if (z) {init12(); z=0;}                                                        
 else {init24(); z=1;}                                                          
}                                                                               
rprint("Loading system...");                                                    
unit=fopen("dsk5.online","w");                                                  
fputs("---",unit);                                                              
fclose(unit);                                                                   
strcpy(as,"DSK5.FLP");                                                          
ea5ld();                                                                        
}                                                                               
                                                                                
answer()                                                                        
{/*pickup the phone..no biggie*/                                                
int flag2;                                                                      
char c;                                                                         
flag2=1;                                                                        
while (flag2)                                                                   
{ puts("\nWaiting for call...\n");                                              
  while (rcvx()==0);                                                            
  clrrs();                                                                      
  crlf=0;                                                                       
  rprint("ATA");                                                                
  sndx(13);                                                                     
  crlf=1;                                                                       
  c=0;                                                                          
  while ((c=waitx())!=13);                                                      
  rinput(as);                                                                   
  if (index(as,"CAR")==0) flag2=0;                                              
  else clrrs();                                                                 
}}                                                                              
