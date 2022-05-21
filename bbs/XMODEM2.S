*                                                                               
       LIMI 0                                                                   
       STWP R0                                                                  
       MOV  R0,@OLDWP                                                           
       MOV  R11,@OLDPC                                                          
       STST R0                                                                  
       MOV  R0,@OLDST                                                           
       MOV  @>83C4,@INTSAV  'INSTALL INTERRUPT ROUTINE                          
       LWPI REGS                                                                
*                                                                               
* SAVE SOME OF PAD WHICH EXTENDED BASIC USES                                    
*                                                                               
       LI   R0,ADDINF                                                           
       LI   R1,SAVPAD                                                           
       LI   R2,10                                                               
SLOOP1 MOVB *R0+,*R1+                                                           
       DEC  R2                                                                  
       JNE  SLOOP1                                                              
                                                                                
*                                                                               
* LOAD R5 WITH THE ROUTINE ADDRESS                                              
*                                                                               
       LI   R5,SENDS1                                                           
       LI   R0,JIFFY                                                            
       MOV  R0,@>83C4                                                           
       LI   R0,4         *DRIVE 4 (TEMP)                                        
       LI   R1,1                                                                
       MOV R0,@FAC                                                              
       MOV  @FAC,R14                                                            
       CLR  R0                                                                  
       INC  R1                                                                  
       LI   R2,XMDNAM                                                           
       LI   R3,'  '                                                             
       LI   R4,10                                                               
XMDL1  MOVB R3,*R2+                                                             
       DEC  R4                                                                  
       JNE  XMDL1                                                               
       LI   R2,XMDLEN                                                           
       LI   R3,>0A00                                                            
       MOVB R3,*R2                                                              
       LI R0,AS                                                                 
       LI R1,XMDLEN+1                                                           
       CLR R2                                                                   
MY#LP  MOVB *R0+,*R1+                                                           
       INC R2                                                                   
       MOVB *R0,*R0                                                             
       JNE MY#LP                                                                
       SWPB R2                                                                  
       MOVB R2,@XMDLEN                                                          
       LI R1,2                                                                  
       LI R2,XMDLEN                                                             
*                                                                               
* GET CRC USAGE...                                                              
*                                                                               
       MOV @CHECK,R0                                                            
       MOV R0,@FAC                                                              
       INCT R1                                                                  
       SETO R6                                                                  
       MOV  @>834A,R2                                                           
       JEQ  USECRC                                                              
       CLR  R6                                                                  
USECRC MOV @SEND,R0                                                             
       MOV R0,@FAC                                                              
       CLR R0                                                                   
       DEC  R1                                                                  
*                                                                               
* SETUP BLOCKS FOR DISK DSR DIRECT FILE ACCESS                                  
*                                                                               
       SLA  R14,8                                                               
       MOV  R14,@>834C  'DRIVE NUMBER AND ACCESS CODE                           
       CLR  @>8350      'POINTER TO INFO BLOCK                                  
       LI   R0,FNAME                                                            
       LI   R1,XMDNAM                                                           
       LI   R2,10                                                               
       BLWP @VMBW                                                               
       MOVB @XMDLEN,R0                                                          
       AI   R0,>0500                                                            
       MOVB R0,@LEN1                                                            
       AI   R14,'0'*256+'.'  'TO MAKE THE CORRECT ASCII DRIVE NUMBER + "PERIOD" 
       MOVB R14,@DRIVE#                                                         
       SWPB R14                                                                 
       MOVB R14,@DRIVE#+1                                                       
       MOV  @>834C,R14                                                          
       MOV  @FAC,R1                                                             
       JEQ  SF                                                                  
       B    @RF                                                                 
*                                                                               
* SEND A FILE USING XMODEM (CHRISTENSEN) PROTOCOL                               
*                                                                               
* GET FILE INFO                                                                 
*                                                                               
SF     BL   @FILE2                                                              
       DATA >0114                                                               
       CLR  R0                                                                  
       MOVB @>8350,R0                                                           
       JEQ  XSJ1                                                                
       LI   R0,1                                                                
       B    @ABORT                                                              
XSJ1   INC  R14         'CHANGE TO READ ONE SECTOR AT A TIME                    
       LI   R0,RECORD                                                           
       LI   R1,>CA53                                                            
XSL1   MOV  R1,*R0+                                                             
       CI   R0,RECORD+128                                                       
       JLT  XSL1                                                                
       LI   R0,HEDDAT                                                           
       LI   R1,RECORD                                                           
       LI   R2,8                                                                
       MOV  R2,R3                                                               
XSL1A  MOV  *R0+,*R1+                                                           
       DECT R3                                                                  
       JNE  XSL1A                                                               
       LI   R0,ADDINF+2                                                         
XSL1B  MOV  *R0+,*R1+                                                           
       DECT R2                                                                  
       JNE  XSL1B                                                               
       MOV  @SEC#,R9                                                            
*                                                                               
* WAIT FOR INITIAL "NAK"                                                        
*                                                                               
XSL2A  CLR  R10                                                                 
XSL2B  BL   @GETACK                                                             
       MOV  R0,R0                                                               
       JEQ  XSL2B                                                               
       CLR  R6                                                                  
       CI   R1,NAK*256                                                          
       JEQ  XSNAK                                                               
XSCRC  SETO R6                                                                  
*                                                                               
* DON'T SEND DIRECTORY HEADER IF IT'S DIS/FIX 128                               
*                                                                               
XSNAK  CLR  @REC#                                                               
       CLR  @SEC#                                                               
       MOV  @>8304,R0   ' IS IT A DIS/FIX 128 FILE?                             
       DECT R0                                                                  
       JNE  XSJ3                                                                
       MOVB @>8307,R0                                                           
       CI   R0,>8000                                                            
       JEQ  XSL3                                                                
XSJ3   BL   @SENDR                                                              
*                                                                               
* LOOP TO READ SECTORS                                                          
*                                                                               
XSL3   BL   @FILE2                                                              
       DATA >0114                                                               
       LI   R0,SECTOR                                                           
       LI   R1,RECORD                                                           
       LI   R2,128                                                              
       BLWP @VMBR                                                               
       BL   @SENDR                                                              
       LI   R0,SECTOR                                                           
       LI   R1,RECORD                                                           
       LI   R2,128                                                              
       A    R2,R0                                                               
       BLWP @VMBR                                                               
       BL   @SENDR                                                              
       INC  @SEC#                                                               
       DEC  R9                                                                  
       JNE  XSL3                                                                
*                                                                               
* SEND "EOT" SINCE WE'RE DONE                                                   
*                                                                               
XSL4   LI   R0,EOT*256                                                          
       BL   *R5                                                                 
       BL   @GETACK                                                             
       MOV  R0,R0                                                               
       JNE  XSL4                                                                
       B    @STOP                                                               
*                                                                               
*                                                                               
* SENDR : SEND ONE RECORD USING THE PROTOCOL, RECEPTION                         
*         OF A (CAN)CEL CHARACTER STOPS XFR                                     
*                                                                               
SENDR  MOV  R11,R15                                                             
       CLR  R10                                                                 
       INC  @REC#                                                               
SENDR1 LI   R0,SOH*256                                                          
       BL   *R5                                                                 
       MOVB @REC#+1,R0                                                          
       BL   *R5                                                                 
       INV  R0                                                                  
       BL   *R5                                                                 
       CLR  R7                                                                  
       CLR  R8                                                                  
       LI   R3,RECORD                                                           
SENDR2 MOVB *R3+,R0                                                             
       BL   *R5                                                                 
       BL   @CRCUPD                                                             
       CI   R3,RECORD+128                                                       
       JLT  SENDR2                                                              
       MOVB R7,R0                                                               
       MOV  R6,R6                                                               
       JEQ  SENDR3                                                              
       MOV  R8,R0                                                               
       BL   *R5                                                                 
       SWPB R0                                                                  
SENDR3 BL   *R5                                                                 
       BL   @GETACK                                                             
       MOV  R0,R0                                                               
       JNE  SENDR1                                                              
       B    *R15                                                                
*                                                                               
* NOW TO GET ACK OR NAK OR WHATEVER...                                          
*                                                                               
GETACK MOV  R11,R13                                                             
       LI   R0,SEC#12                                                           
GETA1  BL   @GETS1                                                              
       JEQ  TRYAGA                                                              
       CLR  R0                                                                  
       ANDI R1,>7F00                                                            
       CI   R1,CAN*256                                                          
       JEQ  GABORT                                                              
       CI   R1,ACK*256                                                          
       JEQ  GETA2                                                               
       CI   R1,NAK*256                                                          
       JEQ  TRYAGA                                                              
       CI   R1,CRC*256                                                          
       JNE  GETA1                                                               
TRYAGA INC  R10                                                                 
       LI   R0,3                                                                
       CI   R10,9                                                               
       JGT  GAB2                                                                
       SETO R0                                                                  
GETA2  B    *R13                                                                
GABORT LI   R0,4                                                                
GAB2   B    @ABORT                                                              
*                                                                               
SENDS1 MOV  @CRUBAS,R12                                                         
SENDS2 TB   22                                                                  
       JNE  SENDS2                                                              
       SBO  16                                                                  
       LDCR R0,8                                                                
       SBZ  16                                                                  
       RT                                                                       
*                                                                               
* END OF ROUTINES TO SEND FILE                                                  
*                                                                               
******************************************************************************* 
*                                                                               
* ROUTINES TO RECEIVE A FILE, SAVES IT AS DIS/FIX 128                           
*   IF IT'S NOT ONE U/L BY FAST-TERM (OR COMPATIBLE PROGRAM)                    
*                                                                               
*                                                                               
RF     LI   R4,CRC*256                                                          
       MOV  R6,R6                                                               
       JNE  CRC#J1                                                              
       LI   R4,NAK*256                                                          
CRC#J1 SETO @FIRST1                                                             
       CLR  R10                                                                 
       CLR  @REC#                                                               
*                                                                               
* LOOP TO GET RECORDS                                                           
*                                                                               
* SEND ACK/NAK FOR LAST RECORD (CRC OR NAK IF THIS IS 1ST)                      
*                                                                               
RDLOOP CLR  R0                                                                  
       MOVB R4,R0                                                               
       BL   *R5                                                                 
SOH1   LI   R0,SEC#10                                                           
SOH2   BL   @GETS1                                                              
       JEQ  SOH3                                                                
       ANDI R1,>7F00                                                            
       CI   R1,CAN*256                                                          
       JNE  MIKE1                                                               
       MOV @FIRST1,@FIRST1                                                      
       JEQ MIKE1                                                                
       LI R0,4                                                                  
       B @ABORT                                                                 
MIKE1  CI   R1,SOH*256                                                          
       JEQ  GOTSOH                                                              
       CI   R1,EOT*256                                                          
       JNE  SOH2                                                                
       B    @RCLOSE                                                             
SOH3   BL   @RECRTY                                                             
       JMP  RDLOOP                                                              
*                                                                               
GOTSOH LI   R0,SEC#10                                                           
       BL   @GETS1                                                              
       JEQ  SOH3                                                                
       CLR  R3                                                                  
       MOVB R1,R3                                                               
       AI   R1,->0100                                                           
       MOVB R1,@TEMPR#                                                          
       CB   R1,@REC#+1                                                          
       JEQ  GOTSO1                                                              
       MOV  @FIRST1,R0                                                          
       JNE  SOH3                                                                
       CB   R3,@REC#+1                                                          
       JNE  SOH3                                                                
*                                                                               
* IT SEEMS THEY MISSED OUR ACK, READ THIS RECORD AND THROW IT AWAY              
*                                                                               
GOTSO1 LI   R0,SEC#10                                                           
       BL   @GETS1                                                              
       JEQ  SOH3                                                                
       AB   R1,R3                                                               
       AI   R3,>0100                                                            
       JNE  SOH3      'CHECK FOR CORRECT HEADER                                 
       LI   R3,RECORD                                                           
       CLR  R7                                                                  
       CLR  R8                                                                  
RCHR1  LI   R0,SEC#10                                                           
       BL   @GETS1                                                              
       JEQ  SOH3                                                                
       MOVB R1,*R3+                                                             
       MOVB R1,R0                                                               
       BL   @CRCUPD                                                             
       CI   R3,RECORD+128                                                       
       JLT  RCHR1                                                               
*                                                                               
* NOW TO GET EITHER THE CRC OR THE CHECKSUM                                     
*                                                                               
       LI   R0,SEC#10                                                           
       BL   @GETS1                                                              
       JEQ  SOH3                                                                
       MOV  R6,R6                                                               
       JEQ  GOTCHK                                                              
       MOVB R1,R0                                                               
       BL   @CRCUPD                                                             
*                                                                               
       LI   R0,SEC#10                                                           
       BL   @GETS1                                                              
       JEQ  SOH3                                                                
       MOVB R1,R0                                                               
       BL   @CRCUPD                                                             
       MOV  R8,R8                                                               
       JNE  SOH3                                                                
       JMP  RECOK                                                               
GOTCHK CB   R1,R7                                                               
       JNE  SOH3                                                                
RECOK  LI   R4,ACK*256                                                          
       CLR  R10                                                                 
*                                                                               
* NOW TO SEND IT TO DISK FILE                                                   
*                                                                               
       MOV  @FIRST1,R0                                                          
       JEQ  RECWRT                                                              
*                                                                               
* OPEN THE FILE                                                                 
*                                                                               
       CLR  @REC#                                                               
       CLR  @FIRST1                                                             
       CLR  @XMDPAB+2                                                           
       LI   R0,RECORD                                                           
       LI   R1,HEDDAT                                                           
       LI   R2,8                                                                
       MOV  R2,R3                                                               
OPNL1  C    *R0+,*R1+                                                           
       JNE  DF128                                                               
       DECT R2                                                                  
       JNE  OPNL1                                                               
       LI   R1,>8302                                                            
OPNL2  MOV  *R0+,*R1+                                                           
       DECT R3                                                                  
       JNE  OPNL2                                                               
*                                                                               
* IT'S A TI/99 FILE (PROBABLY)                                                  
*                                                                               
       BL   @FILE2                                                              
       DATA >0115                                                               
       CLR  @SEC#                                                               
       INC  R14            'CHANGE TO WRITE ONE SECTOR AT A TIME                
       CLR  R0                                                                  
       MOVB @>8350,R0                                                           
       JEQ  UPDATE                                                              
OPERR  LI   R0,2                                                                
       B    @ABORT                                                              
*                                                                               
* IT'S A FILE WE DIDN'T SEND, TAKE IT ANYWAY (AS A DIS/FIX 128 FILE)            
*                                                                               
DF128  LI   R0,OPEN*256+>0003                                                   
       MOV  R0,@XMDPAB                                                          
       BL   @FILE                                                               
       JMP  DFWRT                                                               
*                                                                               
* RECWRT, WRITES A RECORD INTO BUFFER, FLUSHES BUFFER IF FULL                   
*                                                                               
RECWRT MOV  @XMDPAB+2,R0                                                        
       JNE  DFWRT                                                               
       LI   R0,SECTOR                                                           
       LI   R1,RECORD                                                           
       LI   R2,128                                                              
       MOVB @TEMPR#,R3                                                          
       ANDI R3,>0100                                                            
       JEQ  SECW1                                                               
       BLWP @VMBW                                                               
       JMP  UPDATE                                                              
SECW1  A    R2,R0                                                               
       BLWP @VMBW                                                               
       BL   @FILE2                                                              
       DATA >0115                                                               
       INC  @SEC#                                                               
       JMP  UPDATE                                                              
*                                                                               
DFWRT  LI   R0,WRITE*256+>0003                                                  
       MOV  R0,@XMDPAB                                                          
       BL   @FILE                                                               
UPDATE INC  @REC#                                                               
       B    @RDLOOP                                                             
*                                                                               
RECRTY INC  R10                                                                 
       MOV  @FIRST1,R1                                                          
       JEQ  RTY1                                                                
       MOV  R6,R6                                                               
       JEQ  RTY1                                                                
       LI   R4,CRC*256                                                          
       CI   R10,5                                                               
       JLT  RTY3                                                                
       CLR  R10                                                                 
       CLR  R6                                                                  
       JMP  RTY2                                                                
RTY1   CI   R10,9                                                               
       JLT  RTY2                                                                
* DELETE THE INCOMPLETE FILE                                                    
       LI   R0,CAN*256                                                          
       BL   *R5                                                                 
       LI   R0,DELETE*256+>0003                                                 
       MOV  R0,@XMDPAB                                                          
       BL   @FILE                                                               
       LI   R0,3                                                                
       B    @ABORT                                                              
RTY2   LI   R4,NAK*256                                                          
RTY3   B    @RDLOOP                                                             
*                                                                               
RCLOSE MOV  @XMDPAB+2,R0                                                        
       JEQ  RCL2                                                                
       LI   R0,CLOSE*256+>0003                                                  
       MOV  R0,@XMDPAB                                                          
       BL   @FILE                                                               
RCL2   LI   R0,ACK*256                                                          
       BL   *R5                                                                 
       B    @STOP                                                               
*                                                                               
*****************************                                                   
*                                                                               
* ROUTINE TO GET A CHARACTER                                                    
* OR TEST BREAK KEY                                                             
*                                                                               
GETS1  MOV  R0,@TIMER                                                           
GETS1A MOV  @CRUBAS,R12                                                         
       TB   21                                                                  
       JEQ  GOT1                                                                
*                                                                               
* HAVE WE TIMED OUT?                                                            
*                                                                               
       LIMI 2                                                                   
       LIMI 0                                                                   
       MOV  @TIMER,R0                                                           
       JEQ  GETS1B                                                              
*                                                                               
* IS THE SYSOP PRESSING BREAK?                                                  
*                                                                               
       LI   R12,>0024                                                           
       CLR  R0                                                                  
       LDCR R0,3                                                                
       TB   -11       (FCTN KEY)                                                
       JEQ  GETS1C    'NOT PRESSED                                              
       LI   R0,>0300                                                            
       LDCR R0,3                                                                
       TB   -11       ( "4" KEY)                                                
       JNE  GETS1D    'PRESSED                                                  
GETS1C LI   R0,>0600                                                            
       LDCR R0,3                                                                
       SWPB R0                                                                  
       TB   -13                                                                 
       JNE  GETS1E    'JOYST(1,A,B) A=4                                         
       JMP  GETS1A                                                              
GETS1D LI   R0,5                                                                
GETS1E B    @ABORT    'ABORT BY SYSOP                                           
*                                                                               
GOT1   STCR R1,8                                                                
       SBZ  18                                                                  
       CLR  R0                                                                  
       DEC  R0        'TO SET TIMOUT STATUS PROPERLY                            
GETS1B RT             'EQUAL STATUS BIT SET INDICATES TIMEOUT                   
*                                                                               
***************************************                                         
*                                                                               
* INTERRUPT ROUTINE FOR JIFFY TIMER                                             
*                                                                               
***************************************                                         
JIFFY  MOV  @TIMER,R0                                                           
       DEC  R0                                                                  
       JLT  JRET                                                                
       MOV  R0,@TIMER                                                           
JRET   RT                                                                       
***************************************                                         
*                                                                               
* FILE I/O ROUTINES                                                             
*                                                                               
* ROUTINE TO USE A FILE AS DIS/FIX 128                                          
*                                                                               
FILE   LI   R0,SECTOR                                                           
       LI   R1,RECORD                                                           
       LI   R2,128                                                              
       A    R2,R0                                                               
       MOV  R0,@XMDPAB+2                                                        
       BLWP @VMBW                                                               
       S    R2,R0                                                               
       LI   R1,XMDPAB                                                           
       LI   R2,26                                                               
       BLWP @VMBW                                                               
       AI   R0,9                                                                
       MOV  R0,@>8356                                                           
       BLWP @DSRLN2                                                             
       DATA >0008                                                               
       JNE  FILERT                                                              
       LI   R11,OPERR                                                           
FILERT RT                                                                       
*                                                                               
* USE A FILE FOR DIRECT SECTOR ACCESS                                           
*                                                                               
FILE2  MOV  *R11+,R1                                                            
       LI   R0,NAMLEN                                                           
       MOV  R0,@>8356                                                           
       BLWP @VSBW                                                               
       INC  R0                                                                  
       SWPB R1                                                                  
       BLWP @VSBW                                                               
       LI   R0,SECTOR                                                           
       MOV  R0,@ADDINF                                                          
       MOV  R14,@>834C                                                          
       LI   R0,FNAME                                                            
       MOV  R0,@>834E                                                           
       CLR  @>8350                                                              
       BLWP @DSRLN2                                                             
       DATA >000A                                                               
       RT                                                                       
*                                                                               
*                                                                               
DSRLN2 DATA DREGS,DSR1                                                          
*                                                                               
DSR1   MOV   *R14+,R5                                                           
       SZCB  @HEX20,R15                                                         
       MOV   @>8356,R0                                                          
       MOV   R0,R9                                                              
       AI    R9,>FFF8                                                           
       SWPB  R0                                                                 
       MOVB  R0,@VDPWA                                                          
       SWPB  R0                                                                 
       MOVB  R0,@VDPWA                                                          
       NOP                                                                      
       MOVB  @VDPRD,R1                                                          
       MOVB  R1,R3                                                              
       SRL   R3,>8                                                              
       SETO  R4                                                                 
       LI    R2,NAMBUF                                                          
DLOOP1 INC   R0                                                                 
       INC   R4                                                                 
       C     R4,R3                                                              
       JEQ   DJUMP1                                                             
       SWPB  R0                                                                 
       MOVB  R0,@VDPWA                                                          
       SWPB  R0                                                                 
       MOVB  R0,@VDPWA                                                          
       NOP                                                                      
       MOVB  @VDPRD,R1                                                          
       MOVB  R1,*R2+                                                            
       CB    R1,@PERIOD                                                         
       JNE   DLOOP1                                                             
DJUMP1 MOV   R4,R4                                                              
       JEQ   DJUMP6                                                             
       CI    R4,>0007                                                           
       JGT   DJUMP6                                                             
       CLR   @>83D0                                                             
       MOV   R4,@>8354                                                          
       MOV   R4,@SAVE3                                                          
       INC   R4                                                                 
       A     R4,@>8356                                                          
       MOV   @>8356,@SAVE4                                                      
       LWPI  >83E0                                                              
       CLR   R1                                                                 
       LI    R12,>0F00                                                          
DLOOP2 MOV   R12,R12                                                            
       JEQ   DJUMP2                                                             
       SBZ   >00                                                                
DJUMP2 AI    R12,>0100                                                          
       CLR   @>83D0                                                             
       CI    R12,>2000                                                          
       JEQ   DJUMP5                                                             
       MOV   R12,@>83D0                                                         
       SBO   >00                                                                
       LI    R2,>4000                                                           
       CB    *R2,@HEXAA                                                         
       JNE   DLOOP2                                                             
       A     @5*2+DREGS,R2                                                      
       JMP   DJUMP3                                                             
DLOOP3 MOV   @>83D2,R2                                                          
       SBO   >00                                                                
DJUMP3 MOV   *R2,R2                                                             
       JEQ   DLOOP2                                                             
       MOV   R2,@>83D2                                                          
       INCT  R2                                                                 
       MOV   *R2+,R9                                                            
       MOVB  @>8355,R5                                                          
       JEQ   DJUMP4                                                             
       CB    R5,*R2+                                                            
       JNE   DLOOP3                                                             
       SRL   R5,>8                                                              
       LI    R6,NAMBUF                                                          
DLOOP4 CB    *R6+,*R2+                                                          
       JNE   DLOOP3                                                             
       DEC   R5                                                                 
       JNE   DLOOP4                                                             
DJUMP4 INC   R1                                                                 
       MOV   R1,@SAVE5                                                          
       MOV   R9,@SAVE2                                                          
       MOV   R12,@SAVE1                                                         
       BL    *R9                                                                
       JMP   DLOOP3                                                             
       SBZ   >00                                                                
       LWPI  DREGS                                                              
       MOV   R9,R0                                                              
       SWPB  R0                                                                 
       MOVB  R0,@VDPWA                                                          
       SWPB  R0                                                                 
       MOVB  R0,@VDPWA                                                          
       NOP                                                                      
       MOVB  @VDPRD,R1                                                          
       SRL   R1,>D                                                              
       JNE   DJUMP7                                                             
       RTWP                                                                     
DJUMP5 LWPI  DREGS                                                              
DJUMP6 CLR   R1                                                                 
DJUMP7 SWPB  R1                                                                 
       MOVB  R1,*R13                                                            
       SOCB  @HEX20,R15                                                         
       RTWP                                                                     
******************************                                                  
* ABORT ANTHING                                                                 
*                                                                               
* QUERY ABORT                                                                   
*                                                                               
STOP   CLR  R0                                                                  
ABORT  MOV  R0,@>834A                                                           
       MOV  R0,@ERROR                                                           
*                                                                               
* RESTORE PART OF PAB WHICH EXTENDED BASIC USES                                 
*                                                                               
       LI   R0,ADDINF                                                           
       LI   R1,SAVPAD                                                           
       LI   R2,10                                                               
SLOOP2 MOVB *R1+,*R0+                                                           
       DEC  R2                                                                  
       JNE  SLOOP2                                                              
       LI   R1,3                                                                
       CLR  R0                                                                  
       CLR  @>837C                                                              
       LWPI REGS+6                                                              
       MOV  @INTSAV,@>83C4                                                      
       CLR  @>837C                                                              
       RTWP                                                                     
RECORD BSS  128                                                                 
*                                                                               
******************************************************************************* 
*                          CRC SUBROUTINES                                      
*                                                                               
* UPDATE CRC VALUE FROM CURRENT CHAR                                            
* CHAR IN R0 HIGH BYTE                                                          
*                                                                               
* THE CRC POLYNOMIAL IS:                                                        
* X^16 + X^12 + X^5 + 1                                                         
*                                                                               
CRCUPD AB   R0,R7                                                               
       MOV  R0,R1                                                               
       ANDI R1,>FF00     CLEAR LSBYTE                                           
       XOR  R1,R8        XOR NEW DATA WITH OLD CRC                              
       MOV  R8,R1        MOVE TO SCRATCH REGISTER                               
       SRL  R1,4                                                                
       XOR  R8,R1        XOR CRC WITH SCRATCH                                   
       ANDI R1,>FF00     CLEAR LSB                                              
       SRL  R1,4                                                                
       XOR  R1,R8        XOR SCRATCH WITH CRC                                   
       SRC  R1,7                                                                
       XOR  R1,R8        XOR SCRATCH WITH CRC                                   
       SWPB R8           REVERSE BYTES OF CRC                                   
       RT                                                                       
