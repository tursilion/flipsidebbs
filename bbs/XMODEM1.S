       DORG >8300                                                               
ADDINF DATA 0                                                                   
SEC#   DATA 0                                                                   
       BSS  6                                                                   
       DORG >0020                                                               
FNAME  BSS  10                                                                  
NAMLEN DATA >0114                                                               
       DORG >0040                                                               
SECTOR BSS  256                                                                 
       RORG                                                                     
HEDDAT BYTE >07                                                                 
       TEXT 'TIFILES'                                                           
TEMPR# BYTE 0                                                                   
HEX20  BYTE ' '                                                                 
HEXAA  BYTE >AA                                                                 
PERIOD BYTE '.'                                                                 
       EVEN                                                                     
INTSAV DATA >0000                                                               
SAVE1  DATA >0000                                                               
SAVE2  DATA >0000                                                               
SAVE3  DATA >0000                                                               
SAVE4  DATA >0000                                                               
SAVE5  DATA >0000                                                               
NAMBUF BSS  6      'SINCE WE KNOW WERE USING "DSKn."                            
XMDPAB DATA >0000                                                               
       DATA >0000  (NEED "SECTOR"+128)                                          
       DATA >8080                                                               
REC#   DATA >0000                                                               
       BYTE >00                                                                 
LEN1   BYTE >00                                                                 
       TEXT 'DSK'                                                               
DRIVE# BYTE >00                                                                 
XMDLEN BYTE >00    'WILL BE TURNED INTO A PERIOD FOR DSR...                     
XMDNAM TEXT '123456789 '                                                        
SAVPAD BSS  10                                                                  
                                                                                
       EVEN                                                                     
*                                                                               
REGS   BSS  32                                                                  
OLDWP  DATA 0                                                                   
OLDPC  DATA 0                                                                   
OLDST  DATA 0                                                                   
*                                                                               
DREGS  BSS  32                                                                  
TIMER  DATA 0                                                                   
SEC#10 EQU  10*60                                                               
SEC#12 EQU  12*60                                                               
CRUBAS DATA >1340  'CHANGE IF YOU USE SOMETHING OTHER THAN RS232/1              
*                                                                               
FIRST1 DATA 0                                                                   
BRKCNT DATA 0                                                                   
*                                                                               
SOH    EQU 1                                                                    
EOT    EQU 4                                                                    
ACK    EQU 6                                                                    
CAN    EQU 24                                                                   
NAK    EQU 21                                                                   
CRC    EQU 'C'                                                                  
*                                                                               
OPEN   EQU 0                                                                    
WRITE  EQU 3                                                                    
CLOSE  EQU 1                                                                    
DELETE EQU 7                                                                    
*                                                                               
* R04 : ACK FLAG.                                                               
* R05 : ADDRESS OF SENDS1                                                       
* R06 : CRCFLG                                                                  
* R07 : CHKSUM                                                                  
* R08 : CRCVAL                                                                  
* R09 : SECTOR COUNT                                                            
* R10 : IS NUMBER OF RETRIES                                                    
* R14 : DRIVE #                                                                 
*                                                                               
       REF VSBW,VSBR,VMBW,VMBR                                                  
FAC    EQU  >834A                                                               
VDPWA  EQU  >8C02                                                               
VDPWD  EQU  >8C00                                                               
VDPRD  EQU  >8800                                                               
*                                                                               
***************************************                                         
