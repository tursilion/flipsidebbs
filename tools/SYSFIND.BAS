
1 DIM N$(100)
2 PRINT "READING USER LIST"
3 OPEN #1:"DSK5.USERS",INPUT ,DISPLAY ,VARIABLE 80
4 A=0
5 IF EOF(1)THEN 9
6 INPUT #1:N$(A)
7 A=A+1
8 GOTO 5
9 CLOSE #1
10 PRINT A;"USERS FOUND"
11 M=A
12 A=0
14 PRINT "SCANNING FOR SYSOPS..."
20 A$="0"&STR$(A)
30 IF LEN(A$)=2 THEN 50
40 A$=STR$(A)
50 OPEN #1:"DSK5.USER"&A$,INPUT ,DISPLAY ,VARIABLE 80
60 INPUT #1:B$
70 INPUT #1:B$
80 CLOSE #1
90 IF POS(B$,"SYS",1)=0 THEN 110
100 PRINT "USER ";A$;" (";N$(A);")"
110 A=A+1
120 IF A<M THEN 20
130 END
