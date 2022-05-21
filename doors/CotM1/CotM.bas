1 GOTO 10
2 CALL LINK("RINPUT",A$) :: RETURN
4 A :: C :: AS :: DS :: ST :: WS :: LU :: MA :: SL :: X :: Y :: TURNS :: FL :: @X :: @Y :: HURT
5 MST :: MSK :: MN$ :: D$ :: MWS :: LA$ :: TA$ :: KA$ :: UA$ :: EL :: PE :: ER
6 MF :: K :: S :: A$
7 CALL KEY :: CALL JOYST
8 PR :: FLAG
9 DX :: DY :: AX :: AY
10 O=1
15 CALL SIGNON(O,N$)
20 DIM ML(20,20)
21 RANDOMIZE 96
22 !@P-
25 CALL PRINT(O,"Setting up maze.")
30 FOR A=1 TO 20 :: ML(A,1)=1 :: ML(A,20)=1 :: ML(1,A)=1 :: ML(20,A)=1 :: NEXT A
40 CALL LINK("RPRINT",".")
50 FOR A=3 TO 18 :: ML(A,3)=1 :: ML(A,18)=1 :: ML(3,A)=1 :: ML(18,A)=1 :: NEXT A :: CALL LINK("RPRINT",".")
60 FOR A=5 TO 16 :: ML(A,5)=1 :: ML(A,16)=1 :: ML(5,A)=1 :: ML(16,A)=1 :: NEXT A :: CALL LINK("RPRINT",".")
70 FOR A=7 TO 14 :: ML(A,7)=1 :: ML(A,14)=1 :: ML(7,A)=1 :: ML(14,A)=1 :: NEXT A :: CALL LINK("RPRINT",".")
80 FOR A=9 TO 12 :: ML(A,9)=1 :: ML(A,12)=1 :: ML(9,A)=1 :: ML(12,A)=1 :: NEXT A :: CALL LINK("RPRINT",".")
90 FOR A=3 TO 9 STEP 2
100 C=INT(RND*16)+3
110 IF ML(C-1,A)<>1 OR ML(C+1,A)<>1 THEN 100
120 ML(C,A)=0 :: ML(C+1,A-1)=1
130 CALL LINK("RPRINT",".")
140 C=INT(RND*16)+3
150 IF ML(A,C-1)<>1 OR ML(A,C+1)<>1 THEN 140
160 ML(A,C)=0 :: ML(A-1,C+1)=1
170 CALL LINK("RPRINT",".")
180 NEXT A
190 FOR A=12 TO 18 STEP 2
200 C=INT(RND*16+3)
210 IF ML(C-1,A)<>1 OR ML(C+1,A)<>1 THEN 200
220 ML(C,A)=0 :: ML(C+1,A+1)=1
230 CALL LINK("RPRINT",".")
240 C=INT(RND*16)+3
250 IF ML(A,C-1)<>1 OR ML(A,C+1)<>1 THEN 240
260 ML(A,C)=0 :: ML(A+1,C+1)=1
270 CALL LINK("RPRINT",".")
280 NEXT A
290 ML(10,10)=101
300 CALL LINK("RPRINT",",")
310 FOR A=1 TO 5
320 CALL PUT(ML(,),16)
340 NEXT A
350 CALL LINK("RPRINT",".")
360 RANDOMIZE
370 DX=INT(RND*20)+1 :: DY=INT(RND*20)+1 :: IF ML(DX,DY)=1 THEN 370
560 CALL LINK("RPRINT",".")
570 OPEN #2:"DSK5."&SEG$(N$,1,6)&"/P",INPUT,DISPLAY,VARIABLE 80
580 INPUT #2:AS,DS,ST,WS,LU,MA,SL
590 INPUT #2:X,Y
600 CLOSE #2
605 TURNS=100
610 CALL PRINT(O,"")
612 IF MF=0 THEN 615
613 IF ML(X,Y)=0 AND RND>.6 THEN ML(X,Y)=INT(RND*14)+2
615 TURNS=TURNS-1
616 GOSUB 5000
620 CALL PRINT(O,"You are at co-ordinate ("&STR$(X)&","&STR$(Y)&")")
621 MF=0
625 CALL PRINT(O,"You have "&STR$(TURNS)&" turns left.")
626 IF X=DX AND Y=DY THEN GOSUB 10020
627 IF TURNS<0 THEN 6000
630 IF ML(X,Y)<>0 THEN GOSUB 10000 :: GOTO 641
640 CALL PRINT(O,"There is nothing here.")
641 CALL JOYST(1,K,S) :: IF K=0 AND S=0 THEN 650
643 IF K=-4 THEN ST=ST+10
645 IF K=4 THEN AS=AS+5 :: DS=DS+5
647 IF S=-4 THEN MA=MA+5
649 IF S=4 THEN LU=LU+5
650 CALL PRINT(O,"You can go the following directions:")
660 IF ML(X,Y-1)<>1 THEN CALL LINK("RPRINT","NORTH ")
670 IF ML(X,Y+1)<>1 THEN CALL LINK("RPRINT","SOUTH ")
680 IF ML(X+1,Y)<>1 THEN CALL LINK("RPRINT","EAST ")
690 IF ML(X-1,Y)<>1 THEN CALL LINK("RPRINT","WEST ")
695 FL=1
700 CALL PRINT(O,"")
710 CALL PRINT(O,"")
711 IF FL=0 THEN 620
712 FL=0
715 IF LU<1 THEN LU=0
717 CALL KEY(2,K,S) :: IF K=18 THEN PRINT #O:"The Sysop has granted you 10 more turns." :: TURNS=TURNS+10
720 CALL PRINT(O,"What now? (M,P,N,S,E,W,?,Q)")
730 CALL INPUT(O,A$) :: A$=SEG$(A$,1,1)
740 IF A$<>"Q" AND A$<>"M" AND A$<>"P" AND A$<>"N" AND A$<>"S" AND A$<>"E" AND A$<>"W" AND A$<>"?" THEN 730
750 IF A$<>"?" THEN 800
760 CALL PRINT(O,"(M)AGIC")
765 CALL PRINT(O,"(P)OWERS")
770 CALL PRINT(O,"(N)ORTH")
775 CALL PRINT(O,"(S)OUTH")
780 CALL PRINT(O,"(E)AST")
785 CALL PRINT(O,"(W)EST")
790 CALL PRINT(O,"(?) THIS LIST")
791 CALL PRINT(O,"(Q)UIT")
795 GOTO 710
800 IF A$="M" THEN 9000
805 IF A$="Q" THEN 6000
810 IF A$="P" THEN GOSUB 8000 :: GOTO 710
815 MF=1
820 IF A$="N" AND ML(X,Y-1)<>1 THEN Y=Y-1 :: GOTO 610
830 IF A$="S" AND ML(X,Y+1)<>1 THEN Y=Y+1 :: GOTO 610
840 IF A$="E" AND ML(X+1,Y)<>1 THEN X=X+1 :: GOTO 610
850 IF A$="W" AND ML(X-1,Y)<>1 THEN X=X-1 :: GOTO 610
855 MF=0
860 CALL PRINT(O,"You can't walk through walls!") :: GOTO 710
4000 CALL JOYST(2,K,S)
4010 IF S<>-4 THEN 13110
4020 CALL PRINT(O,"You are whisked away by a magic wind!")
4030 CALL PRINT(O,"Please wait for a word of wisdom from the SysOp")
4040 LINPUT A$
4050 CALL PRINT(O,A$)
4060 X=INT(RND*20)+1 :: Y=INT(RND*20)+1 :: IF ML(X,Y)<>0 THEN 4060
4070 GOTO 610
5000 AX=SGN(X-DX) :: AY=SGN(Y-DY)
5010 IF ML(DX+AX,DY+AY)=1 THEN 5500
5020 DX=DX+AX :: DY=DY+AY :: IF DX=X AND DY=Y THEN 10020
5030 RETURN
5500 CALL PRINT(O,"You hear a thump to the")
5510 IF Y>DY THEN CALL LINK("RPRINT","NORTH")
5520 IF Y<DY THEN CALL LINK("RPRINT","SOUTH")
5530 IF X>DX THEN CALL LINK("RPRINT","WEST")
5540 IF X<DX THEN CALL LINK("RPRINT","EAST")
5550 CALL LINK("RPRINT",CHR$(10)&CHR$(13))
5560 RETURN
6000 CALL PRINT(O,"Today's turn is over. Saving game...")
6010 OPEN #2:"DSK5."&SEG$(N$,1,6)&"/P",OUTPUT,DISPLAY,VARIABLE 80
6020 PRINT #2:AS:DS:ST:WS:LU:MA:SL:X:Y
6030 CLOSE #2
6040 CALL PRINT(O,"Returning to main program.")
6050 RUN "DSK5.MAIN"
7000 CALL PRINT(O,"Please wait...")
7010 OPEN #2:"DSK5."&SEG$(N$,1,6)&"/P",OUTPUT,DISPLAY,VARIABLE 80
7020 PRINT #2:0:0:0:0:0:0:0:0:0
7030 CLOSE #2
7090 CALL PRINT(O,"Returning to main.")
7100 RUN "DSK5.MAIN"
8000 CALL PRINT(O,"")
8010 CALL PRINT(O,"Your Powers")
8020 CALL PRINT(O,"---- ------")
8030 CALL PRINT(O,"")
8040 CALL PRINT(O,"Attack Skill:"&STR$(AS))
8050 CALL PRINT(O,"Defense Skill:"&STR$(DS))
8060 CALL PRINT(O,"Stamina:"&STR$(ST))
8070 CALL PRINT(O,"Weapon Strength:+"&STR$(WS))
8080 CALL PRINT(O,"Luck:"&STR$(LU))
8090 CALL PRINT(O,"Magic:"&STR$(MA))
8100 IF SL THEN CALL PRINT(O,"You have Darren slime.")
8110 RETURN
9000 IF MA<3 THEN CALL PRINT(O,"You don't have enough magic for any spells.") :: GOTO 710
9010 CALL PRINT(O,"You have "&STR$(MA)&" magic points.")
9020 CALL PRINT(O,"")
9030 CALL PRINT(O,"Spells")
9040 CALL PRINT(O,"------")
9050 CALL PRINT(O,"TELEPORT - 3 PTS")
9060 CALL PRINT(O,"HURT     - 6 PTS")
9070 CALL PRINT(O,"CURE     -12 PTS")
9080 CALL PRINT(O,"LEARN    -24 PTS")
9090 CALL PRINT(O,"LUCK     -18 PTS")
9100 CALL PRINT(O,"CHARM    -30 PTS")
9110 CALL PRINT(O,"SEE      - 3 PTS")
9120 CALL PRINT(O,"")
9130 CALL PRINT(O,"Enter first 2 letters of spell or nothing to exit.")
9140 CALL INPUT(O,A$) :: A$=SEG$(A$,1,2)
9150 IF A$="" THEN 710
9160 IF A$<>"TE" AND A$<>"HU" AND A$<>"CU" AND A$<>"LE" AND A$<>"LU" AND A$<>"CH" AND A$<>"SE" THEN CALL PRINT(O,"INVALID SPELL") :: GOTO 9140
9170 IF A$<>"TE" THEN 9250
9175 FLAG=0
9180 CALL PRINT(O,"Enter X co-ordinate")
9190 CALL INPUT(O,A$) :: A$=SEG$(A$,1,2) :: CALL NUMVER(A$,A)
9200 IF A=0 THEN CALL PRINT(O,"Invalid number") :: GOTO 9190
9205 @X=VAL(A$)
9210 CALL PRINT(O,"Enter Y co-ordinate")
9220 CALL INPUT(O,A$) :: A$=SEG$(A$,1,2) :: CALL NUMVER(A$,A)
9230 IF A=0 THEN CALL PRINT(O,"INVALID NUMBER") :: GOTO 9220
9231 @Y=VAL(A$)
9232 IF FLAG THEN RETURN
9235 CALL PRINT(O,"("&STR$(@X)&","&STR$(@Y)&"), Are you sure?")
9240 CALL INPUT(O,A$) :: A$=SEG$(A$,1,1) :: IF A$<>"Y" THEN 710
9241 MA=MA-3
9245 X=@X :: Y=@Y :: IF ML(X,Y)=1 THEN CALL PRINT(O,"You materialize inside a wall!") :: GOTO 7000
9246 GOTO 610
9250 IF A$<>"HU" THEN 9300
9260 IF MA<6 THEN CALL PRINT(O,"You haven't enough power.") :: GOTO 710
9270 MA=MA-6 :: CALL PRINT(O,"HURT spell activated.")
9280 HURT=1
9290 GOTO 710
9300 IF A$<>"CU" THEN 9400
9310 IF MA<12 THEN CALL PRINT(O,"You haven't enough power") :: GOTO 710
9320 MA=MA-12 :: CALL PRINT(O,"CURE spell activated.")
9330 A=INT(RND*24)+1 :: CALL PRINT(O,STR$(A)&" stamina restored.")
9340 ST=ST+A :: GOTO 710
9400 IF A$<>"LE" THEN 9500
9410 IF MA<24 THEN CALL PRINT(O,"You haven't enough power.") :: GOTO 710
9420 CALL PRINT(O,"LEARN spell activated.") :: MA=MA-24
9430 A=INT(RND*6)+1 :: CALL PRINT(O,"Skill up by "&STR$(A))
9440 AS=AS+A :: DS=DS+A
9450 GOTO 710
9500 IF A$<>"LU" THEN 9600
9510 IF MA<18 THEN CALL PRINT(O,"You haven't enough magic.") :: GOTO 710
9520 MA=MA-18 :: CALL PRINT(O,"LUCK spell activated.")
9530 A=INT(RND*6)+1 :: CALL PRINT(O,STR$(A)&" luck points added.")
9540 GOTO 710
9600 IF A$<>"CH" THEN 9700
9610 IF MA<30 THEN CALL PRINT(O,"You haven't enough power.") :: GOTO 710
9620 MA=MA-30 :: CALL PRINT(O,"CHARM spell activated.")
9630 A=INT(RND*3)+1 :: CALL PRINT(O,STR$(A)&" points added to weapon.")
9640 GOTO 710
9700 FLAG=1
9710 GOSUB 9180
9720 CALL PRINT(O,"SEE spell activated.")
9730 CALL PRINT(O,"Co-ordinates ("&STR$(@X)&","&STR$(@Y)&")")
9735 MA=MA-3
9740 IF ML(@X,@Y)=0 THEN 9760
9750 CALL PRINT(O,"The section is not empty.") :: GOTO 710
9760 CALL PRINT(O,"The sector is empty.")
9770 GOTO 710
10000 IF ML(X,Y)=101 THEN 12000
10010 ON ML(X,Y)-1 GOTO 10020,10100,10200,10300,10400,10500,10600,10700,10800,10900,11000,11100,11200,11300,11400
10020 CALL PRINT(O,"You have found Darren Crawford!")
10030 MST=INT(RND*60)+1 :: MSK=INT(RND*12)+1
10040 GOSUB 13000
10050 CALL PRINT(O,"The death caused Darren to explode, covering you in")
10060 CALL PRINT(O,"Darren Slime. Besides making you want to throw up, there are no ill effects.")
10070 SL=1
10075 DX,DY=0
10080 RETURN
10100 CALL PRINT(O,"You have met a ghoul.")
10110 MST=INT(RND*12)+1 :: MSK=INT(RND*6)+1
10120 GOSUB 13000
10130 RETURN
10200 CALL PRINT(O,"A zombie faces you.")
10210 MST=INT(RND*18)+1 :: MSK=INT(RND*5)+1
10220 GOSUB 13000
10230 RETURN
10300 CALL PRINT(O,"A giant spider faces you.")
10310 MST=INT(RND*20)+1 :: MSK=INT(RND*10)+1
10320 GOSUB 13000
10330 RETURN
10400 CALL PRINT(O,"You are here with a slime mold.")
10410 MST=INT(RND*12)+1 :: MSK=INT(RND*4)+1
10420 GOSUB 13000
10430 RETURN
10500 CALL PRINT(O,"A skeleton attacks you!")
10510 MST=INT(RND*12)+1 :: MSK=INT(RND*8)+1
10520 GOSUB 13000
10530 CALL PRINT(O,"You take the Skeleton's enchanted shield.")
10540 DS=DS+1
10550 RETURN
10600 CALL PRINT(O,"There is a wumpus facing you.")
10610 MST=INT(RND*20)+1 :: MSK=INT(RND*6)+1
10620 GOSUB 13000
10630 CALL PRINT(O,"Killing the Wumpus increases your luck.")
10640 LU=LU+INT(RND*6)+1
10650 RETURN
10700 CALL PRINT(O,"You must battle a wizard!")
10710 MST=INT(RND*10)+1 :: MSK=INT(RND*14)+1
10720 GOSUB 13000
10730 CALL PRINT(O,"You get increased magic for killing him!")
10740 MA=MA+INT(RND*6)+1
10750 RETURN
10800 CALL PRINT(O,"A giant scorpion is here!")
10810 MST=INT(RND*12)+1 :: MSK=INT(RND*8)+1
10820 GOSUB 13000
10830 CALL PRINT(O,"You take some poison from his tail and put it on your sword.")
10840 WS=WS+1
10850 RETURN
10900 CALL PRINT(O,"A giant ant faces you.")
10910 MST=INT(RND*12)+1 :: MSK=INT(RND*6)+1
10920 GOSUB 13000
10930 CALL PRINT(O,"Your luck is increased.")
10940 LU=LU+INT(RND*6)+1
10950 RETURN
11000 CALL PRINT(O,"You have disturbed a giant wasp!")
11010 MST=INT(RND*12)+1 :: MSK=INT(RND*8)+1
11020 GOSUB 13000
11030 CALL PRINT(O,"You use the venom from the stinger to make a magic potion.")
11040 CALL PRINT(O,"Magic is up.")
11050 MA=MA+INT(RND*6)+1
11060 RETURN
11100 CALL PRINT(O,"A homicidal maniac is attacking you!")
11110 MST=INT(RND*26)+1 :: MSK=INT(RND*6)+1
11120 GOSUB 13000
11130 CALL PRINT(O,"You get some food from the maniac.")
11140 ST=ST+INT(RND*12)+1
11150 RETURN
11200 CALL PRINT(O,"You are faced by an ogre.")
11210 MST=INT(RND*30)+1 :: MSK=INT(RND*10)+1
11220 GOSUB 13000
11230 CALL PRINT(O,"You get some food from the ogre.")
11240 ST=ST+INT(RND*12)+1
11250 RETURN
11300 CALL PRINT(O,"You find a stamina restoring potion!")
11310 ST=ST+INT(RND*24)+1
11320 ML(X,Y)=0
11330 RETURN
11400 READ A$
11410 CALL PRINT(O,"A little man turns to you and says:")
11420 CALL PRINT(O,A$)
11430 CALL PRINT(O,"Then he vanishes.")
11440 ML(X,Y)=0
11450 RETURN
11455 !@P+
11460 DATA THE CREATURE IS NEAR THE CENTER OF THE MAZE
11470 DATA ONLY ONE THING WILL HURT THE CREATURE!
11480 DATA MONSTERS MOVE BUT THE MAZE STAYS THE SAME
11490 DATA MAKE SURE YOU ARE STRONG ENOUGH BEFORE YOU FIGHT THE CREATURE
11500 DATA 'LOOK BEFORE YOU LEAP'
11510 !@P-
12000 OPEN #2:"DSK5.MONSTER",INPUT,DISPLAY,VARIABLE 80
12001 INPUT #2:MN$,D$,MST,MSK,MWS,LA$,TA$,KA$,UA$
12002 CLOSE #2
12010 CALL PRINT(O,"You walk into the room, and are suddenly blinded")
12020 CALL PRINT(O,"By a flash of light and a cloud of smoke!")
12030 CALL PRINT(O,"The smoke clears and "&MN$&" is standing before you!")
12035 CALL PRINT(O,D$)
12040 CALL PRINT(O,"The corpse of "&LA$&" lies in a corner.")
12050 IF SL THEN 12100
12060 CALL PRINT(O,MN$&" pauses, looks at you, and then laughs!")
12070 CALL PRINT(O,"He points at you and the room around you fades out. Suddenly everything")
12080 CALL PRINT(O,"reappears, but "&MN$&" is gone.")
12090 X=INT(RND*20)+1 :: Y=INT(RND*20)+1 :: IF ML(X,Y)=1 THEN 12090
12095 GOTO 610
12100 CALL PRINT(O,MN$&" looks at you, and screams when he sees the slime covering your body!")
12110 CALL PRINT(O,"Everything around you fades out, and you are in a small room")
12120 CALL PRINT(O,"with no exit. "&MN$&" is here. It seems that the time has")
12130 CALL PRINT(O,"come for the final battle. This is to the finish!")
12180 IF HURT=0 THEN 12190
12182 CALL PRINT(O,"Your HURT spell blasts out!")
12184 MST=MST-INT(RND*30+1)
12186 HURT=0
12190 CALL PRINT(O,MN$&"'s stamina is "&STR$(MST))
12200 CALL PRINT(O,"His skill is "&STR$(MSK)&" and his strength is +"&STR$(MWS))
12210 CALL PRINT(O,"Your stamina is "&STR$(ST))
12220 CALL PRINT(O,"Your attack skill is "&STR$(AS))
12230 CALL PRINT(O,"Your defend skill is "&STR$(DS))
12240 CALL PRINT(O,"Your strength is +"&STR$(WS))
12250 CALL PRINT(O,"Your luck is "&STR$(LU))
12260 CALL PRINT(O,"Your magic is "&STR$(MA))
12265 IF MA=0 THEN 12300
12270 CALL PRINT(O,"You may transfer the rest of your magic points to any one of your attributes.")
12275 CALL PRINT(O,"Enter 1 for stamina, 2 for attack skill, 3 for defend skill, 4 for strength or 5 for luck.")
12280 CALL INPUT(O,A$) :: A$=SEG$(A$,1,1) :: CALL NUMVER(A$,A)
12285 IF A=0 THEN CALL PRINT(O,"Enter a number, please.") :: GOTO 12280
12290 IF A$>"5" OR A$<"1" THEN CALL PRINT(O,"1-5, please") :: GOTO 12280
12291 IF A$="1" THEN ST=ST+MA
12292 IF A$="2" THEN AS=AS+MA
12293 IF A$="3" THEN DS=DS+MA
12294 IF A$="4" THEN WS=WS+MA
12295 IF A$="5" THEN LU=LU+MA
12300 CALL PRINT(O,"The battle commences!")
12310 CALL PRINT(O,"YOU-ST="&STR$(ST)&" AS="&STR$(AS)&" DS="&STR$(DS))
12320 CALL PRINT(O,"IT -ST="&STR$(MST)&" SK="&STR$(MSK))
12330 IF MST<1 THEN 12700
12340 IF ST<1 THEN 12900
12341 IF AS<1 THEN AS=0
12342 IF DS<1 THEN DS=0
12343 IF LU<1 THEN LU=0
12350 CALL PRINT(O,"It attacks!")
12360 PR=INT(RND*12)+1+DS
12370 ER=INT(RND*12)+1+MSK
12380 IF ER>PR THEN CALL PRINT(O,"You are hit!") :: ST=ST-INT(RND*2+1)-MWS :: GOTO 12400
12390 CALL PRINT(O,"But you avoid it!")
12400 CALL PRINT(O,"You attack...")
12410 PR=INT(RND*12)+1+AS
12420 ER=INT(RND*12)+1+MSK
12430 IF PR>ER THEN CALL PRINT(O,"You hit it!!!") :: MST=MST-INT(RND*2+1)-WS :: GOTO 12450
12440 CALL PRINT(O,"But you miss!")
12450 IF RND<.65 THEN 12310
12455 A=RND
12460 IF A>.5 THEN 12490
12465 CALL PRINT(O,MN$&" uses "&TA$&"!")
12470 IF INT(RND*12)+MSK>DS+LU THEN A=INT(RND*24)+1 :: ST=ST-A :: CALL PRINT(O,"You are hit! Stamina is down!") :: GOTO 12310
12475 LU=LU-1
12480 CALL PRINT(O,"You avoid the attack!")
12485 GOTO 12310
12490 IF A>.75 THEN 12600
12500 CALL PRINT(O,"He uses "&KA$&"!")
12510 IF INT(RND*12)+MSK>DS+LU THEN A=INT(RND*12)+1 :: AS=AS-A :: DS=DS-A :: CALL PRINT(O,"You are hit! Skill is down!") :: GOTO 12310
12515 LU=LU-1
12520 CALL PRINT(O,"You are not hit!")
12530 GOTO 12310
12600 CALL PRINT(O,MN$&" uses "&UA$&" on you!")
12610 IF INT(RND*12)+MSK>DS+LU THEN A=INT(RND*6)+1 :: LU=LU-A :: CALL PRINT(O,"You are hit! Luck is down!") :: GOTO 12310
12615 LU=LU-1
12620 CALL PRINT(O,"You block the attack.") :: GOTO 12310
12700 CALL PRINT(O,"With a scream of agony, "&MN$&" dies.")
12710 CALL PRINT(O,"You have won the game. Now YOU will become the 'creature of the maze'.")
12720 CALL PRINT(O,"Please answer a few questions.")
12730 CALL PRINT(O,"Press enter to accept the defaults.")
12740 CALL PRINT(O,"")
12745 CALL PRINT(O,"Enter a one line description.")
12750 CALL PRINT(O,"DEFAULT-"&D$)
12755 CALL INPUT(O,A$)
12760 IF A$<>"" THEN D$=A$
12765 IF ST<100 THEN ST=100
12770 CALL PRINT(O,"'Stamina' attack")
12780 CALL PRINT(O,"DEFAULT-"&TA$)
12785 CALL INPUT(O,A$)
12790 IF A$<>"" THEN TA$=A$
12795 CALL PRINT(O,"'Skill' attack")
12800 CALL PRINT(O,"DEFAULT-"&KA$)
12805 CALL INPUT(O,A$)
12810 IF A$<>"" THEN KA$=A$
12815 CALL PRINT(O,"'Luck' attack")
12820 CALL PRINT(O,"DEFAULT-"&UA$)
12825 CALL INPUT(O,A$)
12830 IF A$<>"" THEN UA$=A$
12835 CALL PRINT(O,"Please wait...")
12840 MSK=INT((AS+DS)/2)
12845 OPEN #2:"DSK5.MONSTER",OUTPUT,DISPLAY,VARIABLE 80
12850 PRINT #2:N$:D$:ST:MSK:WS:MN$:TA$:KA$:UA$
12860 CLOSE #2
12870 GOTO 7000
12900 CALL PRINT(O,MN$&" has delivered the death blow!")
12910 CALL PRINT(O,"You are dead. One moment, please.")
12920 OPEN #2:"DSK5.MONSTER",OUTPUT,DISPLAY,VARIABLE 80
12930 PRINT #2:MN$:D$:MST:MSK:MWS:N$:TA$:KA$:UA$
12940 CLOSE #2
12950 GOTO 7000
13000 CALL PRINT(O,"His stamina is "&STR$(MST)&" and his skill is "&STR$(MSK))
13010 CALL PRINT(O,"Your stamina is "&STR$(ST)&" and your attack skill is "&STR$(AS))
13015 CALL PRINT(O,"Your defense skill is "&STR$(DS))
13020 CALL PRINT(O,"At what stamina level would you like to try to escape?")
13030 CALL INPUT(O,A$) :: CALL NUMVER(A$,A) :: IF A=0 THEN CALL PRINT(O,"Enter a number, please.") :: GOTO 13030
13035 EL=VAL(A$)
13040 CALL PRINT(O,"The battle commences!")
13050 CALL PRINT(O,"")
13060 IF HURT=0 THEN 13100
13070 CALL PRINT(O,"Your HURT spell blasts out!")
13080 A=INT(RND*25)+1 :: CALL PRINT(O,"The enemy loses "&STR$(A)&" stamina!")
13090 HURT=0 :: MST=MST-A
13100 IF MST<1 THEN 13500
13105 GOTO 4000
13110 IF ST<1 THEN 13700
13115 IF LU<1 THEN LU=0
13120 CALL PRINT(O,"It swings at you!")
13130 PR=INT(RND*12)+1+DS
13140 ER=INT(RND*12)+1+MSK
13150 IF ER>PR THEN CALL PRINT(O,"It hits you!!") :: ST=ST-INT(RND*2+1) :: GOTO 13170
13160 CALL PRINT(O,"But you avoid it!")
13170 CALL PRINT(O,"You attack...")
13180 PR=INT(RND*12)+1+AS
13190 ER=INT(RND*12)+1+MSK
13200 IF PR>ER THEN CALL PRINT(O,"You hit it!") :: MST=MST-INT(RND*2+1)-WS :: GOTO 13220
13210 CALL PRINT(O,"But you miss!")
13220 IF ST>EL THEN 13300
13230 CALL PRINT(O,"You try to escape.")
13240 IF INT(RND*12)>LU THEN CALL PRINT(O,"You didn't escape.") :: GOTO 13300
13245 LU=LU-1
13250 CALL PRINT(O,"You escaped!") :: CALL PUT(ML(,),ML(X,Y)) :: ML(X,Y)=0 :: GOTO 710
13300 IF ML(X,Y)<>5 AND ML(X,Y)<>10 AND ML(X,Y)<>12 THEN 13400
13310 IF ML(X,Y)=5 THEN CALL PRINT(O,"The spider shoots web at you!")
13320 IF ML(X,Y)=10 THEN CALL PRINT(O,"The scorpion attacks with it's tail!")
13330 IF ML(X,Y)=12 THEN CALL PRINT(O,"The wasp attacks with it's stinger!")
13340 IF INT(RND*12)>LU THEN A=INT(RND*9+1) :: AS=AS-A :: DS=DS-A :: CALL PRINT(O,"You are hit! Skill is down.") :: GOTO 13400
13345 LU=LU-1
13350 CALL PRINT(O,"You manage to dodge the attack!")
13400 CALL PRINT(O,"YOU-ST="&STR$(ST)&" AS="&STR$(AS)&" DS="&STR$(DS))
13410 CALL PRINT(O,"IT -ST="&STR$(MST)&" SK="&STR$(MSK))
13415 IF AS<1 THEN AS=0
13417 IF DS<1 THEN DS=0
13420 GOTO 13100
13500 CALL PRINT(O,"The monster is dead!")
13510 A=INT(RND*ML(X,Y))+1 :: CALL PRINT(O,"You gain "&STR$(A)&" skill.")
13520 AS=AS+A :: DS=DS+A
13525 ML(X,Y)=0
13530 RETURN
13700 CALL PRINT(O,"You have been killed!")
13710 CALL PRINT(O,"Sorry, your game is over.")
13720 GOTO 7000
24999 !@P+
25000 SUB PRINT(X,A$)
25005 IF LEN(A$)>80 THEN CALL LINK("RPRINT",SEG$(A$,1,79)) :: A$=SEG$(A$,80,80)
25010 CALL LINK("RPRINT",A$&CHR$(10)&CHR$(13))
25030 SUBEND
25040 SUB INPUT(X,A$)
25045 CALL LINK("RPRINT",">")
25050 GOSUB 2
25060 CALL LINK("RPRINT",CHR$(10)&CHR$(13))
25070 SUBEND
25080 SUB PUT(ML(,),N)
25090 X=INT(RND*20)+1 :: Y=INT(RND*20)+1
25100 Q=ML(X,Y) :: IF Q=1 OR Q=101 OR Q=2 THEN 25090
25110 ML(X,Y)=N
25120 SUBEND
25130 SUB SIGNON(O,N$)
25140 REM
25150 OPEN #2:"DSK5.PLAYERS",INPUT,DISPLAY,VARIABLE 80
25160 CALL PRINT(O,"Enter your name:")
25170 CALL INPUT(O,A$)
25171 CALL PRINT(O,"'"&A$&"'  Press enter if correct or re-enter if not.")
25172 CALL INPUT(O,B$) :: IF B$<>"" THEN A$=B$ :: GOTO 25171
25180 CALL PRINT(O,"Enter password")
25190 CALL INPUT(O,B$)
25191 CALL PRINT(O,"'"&B$&"'  Press enter if correct or re-enter if not.")
25192 CALL INPUT(O,C$) :: IF C$<>"" THEN B$=C$ :: GOTO 25191
25195 IF EOF(2)THEN 25300
25200 INPUT #2:C$,D$
25210 IF C$<>A$ THEN 25195
25220 CLOSE #2 :: N$=A$
25230 IF B$<>D$ THEN CALL PRINT(O,"Wrong password.") :: GOTO 25150
25235 OPEN #2:"DSK5."&SEG$(A$,1,6)&"/P",INPUT,DISPLAY,VARIABLE 80 :: INPUT #2:A :: CLOSE #2 :: IF A<>0 THEN 25240
25236 CALL PRINT(O,"Re-vitalizing player.")
25237 GOTO 25340
25240 SUBEXIT
25300 CLOSE #2 :: CALL PRINT(O,"Name not found. Have you played before?")
25302 CALL INPUT(O,A$) :: A$=SEG$(A$,1,1)
25304 IF A$<>"Y" AND A$<>"N" THEN CALL PRINT(O,"Y or N please.") :: GOTO 25302
25306 IF A$="Y" THEN 25150
25308 CALL PRINT(O,"Adding to player list...")
25310 OPEN #2:"DSK5.PLAYERS",APPEND,DISPLAY,VARIABLE 80
25320 PRINT #2:A$:B$
25330 CLOSE #2
25335 RANDOMIZE
25340 OPEN #2:"DSK5."&SEG$(A$,1,6)&"/P",OUTPUT,DISPLAY,VARIABLE 80
25345 RANDOMIZE
25350 PRINT #2:INT(RND*12)+1
25360 PRINT #2:INT(RND*12)+1
25370 PRINT #2:INT(RND*24)+2
25380 PRINT #2:INT(RND*2)+1
25390 PRINT #2:INT(RND*12)+1
25400 PRINT #2:INT(RND*6)+1
25410 PRINT #2:0
25420 PRINT #2:2:2
25430 CLOSE #2
25440 N$=A$
25450 SUBEND
26000 SUB NUMVER(A$,A)
26005 IF A$="" THEN A=0 :: SUBEXIT
26010 FOR A=1 TO LEN(A$)
26020 IF SEG$(A$,A,1)>"9" OR SEG$(A$,A,1)<"0" THEN A=0 :: SUBEXIT
26030 NEXT A
26040 A=1 :: SUBEND
27000 SUB ERROR(O)
27010 CALL ERR(EC,ET,ES,EL)
27020 CALL PRINT(O,"An error occurred.")
27030 CALL PRINT(O,STR$(EC)&" "&STR$(ET)&" "&STR$(ES)&" "&STR$(EL))
27040 CALL PRINT(O,"Please leave a comment and quote these numbers.")
27050 CALL PRINT(O,"Returning to main...")
27060 RUN "DSK5.MAIN"
27070 SUBEND