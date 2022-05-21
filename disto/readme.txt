==========
BACKGROUND
==========

FlipTerm/FlipSide was originally coded in 1991 in Ottawa, where it ran until late 1994.
It's a custom BBS package written largely in c99. It was called FlipTerm because originally
it was meant to be a terminal package.

FlipTerm BBS is pretty strongly hard-coded - making changes will generally require either recompiling the program, or hex-editting the files (in which case strings need to be kept shorter or the same length as the original). Sorry. It was never intended as a general purpose BBS. In addition, some of the executables are lost (although we have source), and setting it up is a mess. 

On the other hand, for the sake of history and perhaps someone learning a neat trick from the code, I've created this package. These docs are to be the best that I can recollect!

FlipTerm BBS software may be freely distributed, modified, and redistributed. All I ask is that all distributions include credit to the original in the program or included documentation as follows:

Original program by Mike Brent aka Tursi - http://harmlesslion.com

=====
FILES
=====

Here is what we have. The program is written in c99 with some embedded assembly support code. it includes main menu, questionaires, sysop menu, message bases, and some online games.

FlipTerm is meant to be run from a Horizon RAMdisk. It resets the system after each user, so if you don't use a RAMdisk, you need a way to automatically launch the loader!

Except for those few things you can explicitly configure (message bases and door games),
everything is expected to be stored on DSK5 when running.

---------
Programs:
---------
COT/COU/COV - Creature of the Maze 2 - Dungeon crawl roleplaying game
FSL - FlipSide Loader - this program should be loaded on the RAMdisk as 'MENU' to autoboot
SYS/SYT - Sysop menu
FLP/FLQ/FLR - Main menu program
TAR/TAS/TAT - Tarot reader door program
SYSFIND - scans users for Sysop access
OCEANARC - program that archived one of the message bases

Unfortuantly, the executables for the Online Doors (DOR), Russian Roulette (RUS) and the Message Bases (MSG) are missing and would need to be built from source.

-------------------------------------------
Source (it looks like everything is here!):
-------------------------------------------
CFIO - c99 object code for formatted IO functions
COTM;c/COTM;C2 - c99 source code for Creature of the Maze 2
DOOR;C - c99 source code for door game menu
FILES;C - c99 Xmodem based file transfor code
FLIP;C/FLIP;C2 - c99 Source code for main menu
FLIPUTILS - Shared c99 file containing functions used by all modules
FSL;C - c99 FlipSide loader v2.0 with Fidonet (but never proven to work!)
FSL;OLD - c99 code for FlipSide Loader v1.0
MESSAGE/MESSAGE2 - Message base processor c99 code
RANDOM;C - Clint Pulley's c99 Random number code
RUS;C - c99 Source code for Russian Roulette game
STDIO - c99 STDIO include file
STRINGFNS - c99 string functions by Tom Wible
SYSOP - c99 Source code for the Sysop Menu
TAROT;C -  c99 Source code for Tarot reader game
XMODEM1/XMODEM2 - XModem Assembly code based on code by Paul Charleston

------------
Config files
------------
Unfortunately I only have these as examples in PC format. Most of them you will
need to construct for your particular setup anyway. Open them in Notepad or any
other text editor, but you need to create the real ones on your TI.

TITLE - original title ASCII art
CONFIG - main BBS configuration (you must create this file!)
  Line 1: Unused, can leave blank
  Line 2: First digit is the number of online game credits each login gets. The
          rest of the line is the new user message base mask. Three digits that
          set the initial value for each message base (normally 000). You can restrict
          new users from a message base by using '***' instead. These three digits
          repeat till the end of the line.
  Line 3: name of the first message base. The first characters are significant and
          must be: "A - (010) Title goes here". The 'A' indicates the letter to be
          pressed and must be first, followed by a space, followed by a dash, then
          another space, a parenthesis, and three digits indicating the maximum
          number of messages in this message base. (In this case, that value is 10).
          After that the rest of the line may be any text to display a name. When the
          maximum count is reached, older messages are deleted.
  Line 4: Prefix path for the message base. Three digits are appended to this path
          to get the file name for each message. For instance, DSK5.NEW would indicate
          that the message filenames will look like: DSK5.NEW001, etc. Filenames wrap
          at 999 back to 000, but since a TI disk only supports 127 files (and the
          BBS only support 999 messages in a base anyway), that shouldn't be a problem.
  For more message bases, you may repeat lines 3 and 4 for letters B-Z. The first
  message base is special as it is where new user questionaires are placed!
CREDS - auto generated - contains the number of door credits a user has left.
COTM2DATA - Player data for Creature of the Maze 2
  Line 1: Player BBS name
  Line 2: Player game Alias
  Line 3: Stats: abc123....eeefff...ggg
          a - level
          b - x position
          c - y position
          1 - number of 'hurt' spells
          2 - number of 'shield' spells
          3 - number of 'heal' spells
          eee - skill
          fff - stamina
          ggg - hitpoints (life)
          ... - unused? Set to 0.
  Line 4: Gold (must be 4 digits): ie: 0100
  (repeat for each player)
BOSS - Creature of the Maze boss data file:
  Line 1: Boss name (usually a previous player)
  Line 2: Boss description (entered by that previous player)
  Line 3: Stats - 3 three digit numbers: aaabbbccc
          aaa - stamina
          bbb - skill
          ccc - hit points (life)
LEVEL0/LEVEL9 - Mazes for each level. Consist of 10 rows of 10 characters
                representing the maze. The maze generator is lost but you
                could make your own - ensure the entire border is set as
                walls to prevent players from walking out of the maze. The
                valid characters are as follows:
                # - Wall
                $ - Empty passage
                % - Store
                & - Stairs up a level
                ' - Stairs down a level
                + - trapdoor (drops you a level, don't place on level 9)
                . - Final boss (usually the center of level 9)
                I didn't prepare examples for this one - have fun. ;)
                          
DATE - Created in the SYSOP menu, contains an arbitrary string containing the current   
       date. Since there is no clock support, someone with access to the sysop menu
       usually changes this. It's placed into each message.          
FEEDBACK - autogenerated file that logs activity and feedback from users
FIRSTMES - A list of digits containing current first message of each message base, 
          each three digits. You should initialize this to a line of 000's, enough for
          all bases
LASTMES - same as FIRSTMES, but the last message number in each message base. Initialize
          it the same way.
LOGIN - A login message you can display to users after they login.
NQUEST - A new user questionaire - this is a list of questions presented to new users
         when they login. The results are posted in the first message base. If a new user
         fails to complete the questionaire, their account is not saved.
ONLINE - auto-generated file containing the name of the currently online user
ONLINLIST - list of online games which the door program can load:
  Line 1 - Name of the game - displayed to the user (no need for selection key)
  Line 2 - Path to the EA5 loadable game, filename must be exactly 3 characters 
           (for example: DSK3.RUS). Multiple EA5 files in the standard manner
           are fine (ie: RUS/RUT, etc.
QUESTLIS - list of users who have performed the standard login questionaire already. When
           you post a new questionaire you may want to manually clear this list.
QUESTS - Same idea as NQUEST, but this login questionaire is presented to all users when
         they log in.
USERS - A simple list of names for users. The first row corresponds to USER00 and should
        probably not be used. The rest are used to match a name to a number by row. You will
        probably need to manually add yourself as a sysop in the next line, and fill
        in USER01 manually. Names in this file MUST be uppercase - you can block the first
        row trivially by using a lowercase string.
USER00 - Sample template for a user. You probably want to create USER01 for yourself:
  Line 1: Password. This is unencrypted, so treat accordingly.
  Line 2: Access level. May be: "NORMAL" (normal access), "RESTRICTED" (no games or message
          bases), or "SYSOP" (actually anything with SYS in it - Sysop menu)
  Line 3: Help level and paging - used to manage menus. First 5 characters must be
          either "FULL " (note space) or "BRIEF" - only the first character is checked but
          five characters are needed. Full displays the menu, Brief shows only the summary.
          After that is the optional 'More' paging prompt - two digits representing the
          number of lines to count (usually 24), and then a 'Y' (paging enabled) or 'N'
          (paging disabled). The user can change these values inside the program so it
          is easiest if manually creating the file to just set 'Full' and leave the rest.
  Line 4: List of digits similar to the message base mask in CONFIG - here the numbers are
          updated by the program to represent the last message read in each message base.
          Any base tagged with *** represents a base the user has no access to.
FILES - this is a simple list of available files dumped to the user. Since it's read as
        a simple text file, you can include descriptions if you like. It is not 
        automatically updated.
FILEINFO - This text file is where you put policies to display in the file menu.

=====
Usage
=====

If you get it all set up, I would heartily congratulate you! The one external hack
required is that it expects DTR on the modem line to run through the cassette control
2 line - this connection is broken on reset to hang up the modem. The BBS watches the
modem for 'RING' and will send 'ATA' (auto answer should not be set on the modem).

There are a lot of references to 'Flipper' - this was me as the sysop back then. Also,
note that the 'captures' below are simulated!

First program to run is FSL, which is meant to be renamed to 'MENU' and run as the
boot program on a Horizon RAMdisk.

Anyway, it runs both over RS232 and local keyboard. When someone connects, it will 
cycle through 1200 and 2400 baud, waiting to receive a recognizable 'enter' key. After
it does, it will launch FLP, the main program.

The sysop may interrupt at any time to get a mini sysop menu by pressing a control
key, I *think* it's control-period. This mini menu lets you enter a chat mode with the
user, hang up on the user, jump to the main sysop menu, change the baud rate (the
'infinite' option is useful for local use as it speeds up the output), or return control
to the user.

----------------------------------------
Flipper's here...just a second...
 
What now, Flip?
-------------
1) enter chat mode
2) boot user off
3) enter sysop menu
4) set RS to 1200 baud
5) set RS to 2400 baud
6) set RS to 'infinite'
0) return control to user

Current user is: Username
----------------------------------------

The BBS also supports Control-S and Control-Q to suspend and resume text, and most
file displays can be aborted by pressing enter/return. Most input is single key based
(ie: you just press the menu option, you don't have to press enter except when entering
strings).

============
MAIN PROGRAM
============

Login looks something like this:

----------------------------------------
Flip Side Loader - Horizon boot routine v1.1
by Mike Ward

REALITY.SYS corrupted. Press <return> to reboot universe.

Loading system...

The FLIP Side! BBS By Mike Ward
Written in c99. version 1.3

       <RETURN> = abort    <Control>-S = pause   <Control>-Q = Continue
>>>>>>>>>IBM/ATARI USERS: use <BACKSPACE>, not the cursor arrow keys!!<<<<<<<<<
+-------W-e-l-c-o-m-e---t-o---T-h-e---F-L-I-P---S-I-D-E---B-B-S-!-!-!---------+
:/                       /-\           |         .      |      .           | \:
:            /-\                       |                                  . ..:
:                   ###                |  .          .           . . .. ..... :
: +                #####               |   ****    '        . .......... .....:
:+-+               #####               |******o*     .... ...... .... ....    :
::#:   \-/          ###      \-/  *****************..... ... ......         ##:
:+-+                              . *************...'. .....  .            ###:
:! ]                                ********. ... ..                 .    ###::
:! ]                             . ****** *. ..                          ###:::
:! ]-----------------------------*****-|..*   |     '      .             ##::::
:! ]]                ++     .   ****   |     -*-                .        ##::::
:! ]]^^^^^^^^^^^^^^^^++^^^^^^^^***^^^^^|      |      '.                  #:::::
:__. ]              ++++   .***** .   .|                                  :::::
:  \_].\/\/\/\/\/\/\+/++/\.\.\***\/\/\/|      .       '                    ::::
:. \ \].            ++ +    . . * .    |               :       |            :::
:     ]./\ /\ /\ /\++++++ /. /\./\ /\ /|.              '.     -*-     .       :
:\ . \ ]..         ++ ++. . .. .       |                .'.    |             /:
+-------------------------------------------------------------------------(MW)+
          Version 1.2   Written in c99 by Mike Ward   Sysop: Flipper
           Co-Sysops: TIger, Feral Ferret (not by choice), Phantom
           Running on a TURBO Texas Instruments 99/4A Home Computer

Please enter your handle: 
Tursi
Scanning...
Oh yeah? What's your password?
*********
Hi there, TURSI

We'rrrrrrrrrrrrrrre baaaaaaaaaaaaaaa-ack!

The Flip Side, main menu
------------------------

1) Message chatter
2) Online diversions
3) Utility
4) Call for Flipper
5) Feed Flipper
6) Sysop menu (for sysops)
7) Get out of here!

Press the # of your choice
----------------------------------------

The questionaires, not shown here, are pretty strict and force the user to enter more than
two characters (meant to block "y" or "n" answers). 

Message chatter would load MSG, the message forums.

Online diversions loads DOR, the online door/game menu.

Utility brings up a small utility/options menu.

Call for Flipper plays an audible chime to summon the sysop.

Sysop menu, if the user has SYSOP access, loads SYS, the sysop menu.

Get out of here! logs the user out after confirmation.

These are detailed below.

=================
Message Processor
=================

For a system without ANSI support or a full screen editor, the message system was pretty
well received by people and logged literally thousands of messages. It was the main purpose
of the board and saw a lot of use.

Message bases are configured in the main CONFIG file, as well as FIRSTMES and LASTMES.
Each user file has a line dedicated to the message bases too.

Entering the message processor looks like this.
----------------------------------------
Mini Message Processor v2.0
----------------------
[C]hange message base
[R]ead single
[F]orward read
[B]ackward read
[N]ew read
[!]Quickscan New
[E]nter message
[Q]uit to main

A - (100) General Message Discussion
Last message you read: 010
First message #005
Last message  #022
----------------------------------------

Change message base brings up a list of configured message bases. The user may
then select a new one to browse.

Read Single lets the user enter a message number to read just that message. Reading
just the last message, for instance, is a quick way to catch up on a base.

Forward read will ask the user for the first message number, and one at a time display 
each message to the user, incrementing inbetween.

Backward read will do the same as forward read, but decrements the message number.

New read will perform a forward read that automatically starts with the first new
message in that base.

Quickscan New will automatically perform a 'new read' operation in every message base the
user has access to.

Enter message allows the user to enter a new message in the current message base. 

Quit to main reloads FLP, the main BBS menu.

When reading a message, the message is displayed like so:

----------------------------------------
TO:OPUS
From:FLIPPER
Date:21st of June.  Like, grr.
Reply to 949
 
I'm not a big fan of Akira. I saw Akira, it was interesting. Not really my 
type of movie, though.
 
I believe Rogue is a big Akira fan.

[a]gain, [N]ext, [t]hread, [r]eply, [q]uit
----------------------------------------

Again will display the same message again - useful for messages that scrolled off the
screen.

Next will display the next message using the current message counting order. If there
is no next message then it will return to the main menu. This option is the default if
enter alone is pressed (indicated by uppercase letter).

Thread, if the message is a reply, will display the original message. On that message,
the options "[t]hread, [Q]uit" are available - thread here allows you to thread back
again if the message is a reply. Quit will return back to the first message that was
threaded from (default action).

Reply will set up a reply action to this message, and enter the editor.

Quit will return to the message board menu.

Entering a message looks something like this:

----------------------------------------
sec...
To:Flipper
Private? (y/N) Nah.
Enter your message now. Enter a blank line to end.
>I think Akira was a great movie. So there.

[C]ontinue, [A]bort, [S]ave, [L]ist, [E]dit?
----------------------------------------

The 'to' option is freeform. It may be entered as 'All' (or really anything else).
'All' will inhibit the 'Private?' question, however. If private, the userlist is scanned
to make sure the entered name is valid. Note that Sysops can see all private messages.

The message processor supports up to 50 lines in a message, and has a line-based
editor to make minor edits possible.

Continue will return to the editor in case the user hit a blank line by accident. Note
that paragraphs can be done by typing a space before hitting enter.

Abort will ask the user to clarify, then cancel the entry of the message.

Save will save the message to disk then return to the menu.

List will show the message in progress to the user.

Edit brings up a small editor:

----------------------------------------
1:I think Akira was a great movie. So there.
[A,B,C,I,D,Q,0-9,?] ?
Editor:[A]head, [B]ack, [C]hange line
[I]nsert line, [D]elete line, [Q]uit
[0-9] change step (0=10)
----------------------------------------

Ahead goes to the next line (or skips ahead if the step is set higher than 1)

Back goes to the previous line (or skips back depending on step)

Change Line brings up the input prompt to allow the user to retype this line.

Insert Line inserts a blank line before this one and lets the user type it.

Delete Line deletes the currently displayed line.

0-9 changes the step value to get to a particular line quicker

Quit returns to the main message entry prompt.

============
Online Games
============

The online doors program could launch EA5 programs, but generally you would
want programs written for FLIPUTILS in order to have the sysop key support, the
RS232 interface, and the (manual) return to the main program on exit. As with
all parts of FlipTerm, filenames were limited to 3 characters.

Entering it looks something like this:

----------------------------------------
Flip Side Online Menu
---------------------
A=Russian Roulette
B=Creature of the Maze 2
C=Tarot Reader
0 - return to main menu

You have 5 online credits.
----------------------------------------

The menu is configured in the ONLINLIST file. It's pretty straight forward, the user
makes a selection, their credits are decremented by one, and the program is loaded.

If the user runs out of credits, they are returned automatically to the main menu.

=========
Utilities
=========

Entering the utilities menu gives the following list:

----------------------------------------
Your current stats
------------------
Name:TURSI
Password: [not shown]
Main menu help level:FULL
Security level:NORMAL

1 - change password
2 - change help level
3 - see user list
4 - see last callers
5 - change 'more' prompt
0 - exit to main
----------------------------------------

Change password prompts the user to enter a new password for themselves.

Change help level toggles between 'FULL' and 'BRIEF'. In brief mode the main menu is just
a single summary line ('?' will always bring up the full text in that case).

See user list dumps a list of all registered usernames.

See last callers opens the feedback file, and dumps a list of logins.

Change 'more' prompt lets the user set how many lines to page at, or turn the prompting
off altogether.

=================
Sysop Harrassment
=================

Call for Flipper plays chimes to get the Sysop's attention. If the sysop wants to chat,
he can use the key sequence described above to break in.

----------------------------------------
Hey Flipper! Opus wants to talk to you!!

Paging....

Well...he can't stand those chimes,
so if he's around he'll break in.
If he doesn't, well.....I tried!
Leave feedback if no answer.
----------------------------------------

Feed Flipper lets the user add a note to the feedback file (note this is not meant to be
displayed in the 'last callers' utility option). Entering a blank line saves the feedback.

==========
Sysop Menu
==========

Selecting the Sysop menu, if you have access, gives you this menu:

----------------------------------------
Yeah, yeah. Just a minute...

Flip Side: Sysop
----------------
1 - view/modify user stats
2 - view user list
3 - read feedback
4 - add login bulletin
5 - set message date
6 - add user
0 - exit to main

(1-5,0):
----------------------------------------

View/Modify user stats gives a simple user editor:

----------------------------------------
Enter user name to modify
>Opus

User name:OPUS
User #002
Password:Salmon123
Security level:NORMAL
Message base access (*=banned):
 A - (010) General Conversation
*B - (100) Secret Anti-Penguin Base
 C - (050) Friends of the Penguin

Press P to change password
Press S to change security level
Press R to restrict a msg base
Press C to clear a msg base
Anything else to continue
----------------------------------------

Pressing P will let you enter a new password for this user.

Pressing S will let you change the user's access level to "CO-SYSOP", "NORMAL", or
"RESTRICTED". These are documented up in the user file section.

Pressing R will ask you to select a message base, then ban that user's access to it
by flagging it with asterisks. Note that restricted is not hidden - the user can still
see the base, they just can't post.

Pressing C will do the same, but will clear the ban and reset that user's last read
count to 000.

Viewing the user list will provide a list of all registered users. It differs from
the public user list by including each user number.

----------------------------------------
00    dummyuser
01    TURSI
02    OPUS
----------------------------------------

Read feedback will simply dump the feedback file.

Add login bulletin will append a new bulletin to LOGIN, separated by a dashed line.

Set message date will update DATE with a new string. (I used my co-sysops to set this.
They had great fun placing taunts and teases in with the date.)

Add user allowed the creation of a new user without requiring that user to log in:

----------------------------------------
Add new user? (y/N)
>Y
User #03
Enter new user's name.
>Jackie
Enter password.
>ilikeicecream
Saving new user...
----------------------------------------

The user is created with the FULL menu setting and NORMAL access. They get to
bypass the new user questionaire this way.

===========
Logging off
===========

Get Out of Here lets the user leave the BBS.

----------------------------------------
WHAT?! Leave the Flip Side? Are you sure?? ([Y]/n) n
Temporary insanity...

WHAT?! Leave the Flip Side? Are you sure?? ([Y]/n) y
OK...bye OPUS. Call again

Goodbye, OPUS
Returning you to reality...
----------------------------------------

There is also an idle timeout of about 5 minutes, if no entry is made at any prompt:

----------------------------------------
Press the # of your choice
Universe becoming unstable...
Universe collapses.
----------------------------------------

================
Russian Roulette
================

This is a simple little game - you decide whether to press enter or chicken out.

Each time you press enter, there is a chance of the 'gun' firing and your connection
is hung up. 

If you fire a certain number of times and win, you get extra game credits. Currently
there is a 1 in 4 chance of losing, and you need 10 pulls to win. It used to be simpler
but the users complained they were winning when they wanted to disconnect. ;)

----------------------------------------
Welcome to Russian Roulette, comrade.
(version 1.2)

Instructions? (y/n)
>y
Here you will gamble with your connection
with a loaded pistol. The pistol has four
chambers and 1 bullet. You will pull the
trigger by pressing enter. If the trigger
goes off...you will be disconnected.
If you pull the trigger 10 times (without
being killed) you will win the game!
(and get some extra credits!)
NOTE: the chamber is spun between each pull
if you don't want to pull the trigger
(i.e. chicken out) type 'a' for abort and
press enter.

Pull #1
Press enter <a=abort>:>!CLICK!<
Pull #2
Press enter <a=abort>:>!CLICK!<
Pull #3
Press enter <a=abort>:!!!!! >>> --- BANG --- <<< !!!

LOSER!! LOSER!! LOSER!! LOSER!! LOSER!! LOSER!!
(you are dead! Call again!
----------------------------------------

======================
Creature of the Maze 2
======================

This is a simple dungeon crawl. I have a Creature of the Maze 3 on my website, but this
was the last version running on the TI itself.

I'm not going to go into detail on all the menus - if you get it going, it's pretty self
explanatory. But since I don't have any maze files it may be a pain to get it going. :)

See the files section for a description of its data files if you want to try.

============
Tarot Reader
============

This is a really simple Tarot reading program.

----------------------------------------

Greetings, OPUS
I am Tee-Eye, the mystical sayer of sooth.
Would you like me to tell you what the cards have in
store for you? (press Y or N) Y

Would you like a brief explanation? (Y/N) Y

Tarot reading is an ancient art that goes back hundreds,
if not thousands, of years. Tarot cards are brightly
coloured cards, with divinitory meanings hidden in the
pictures. The deck is similar to a regular playing deck,
but larger. There are two parts, called 'Arcanas'. The
'Major Arcana' contains the 'picture' cards. These cards
are all independant of the others, and tend to have a
more definite meaning attached. Examples are 'The Star',
or the well-known 'Death'.
The 'Minor Arcana' has four suits (Swords, Wands, Cups and
Pentacles), each with 14 cards (Ace-10, Page, Knight, 
Queen and King). The cards are layed out an interpreted
by where and how they lay. This program will take care
of interpretation for you.

A computer can only give general meanings. Not all the
meanings given necessarily apply. You must decide for
yourself what the cards are trying to tell you.
---Press a key---

First we must choose a significator, a card to represent you.
Please answer these questions as honestly as possible.

How old are you?
1: 16 or under
2: 17-25
3: over 25
3

Are you:
1: male
2: female
1

Are you:
1: neutral
2: easy-going
3: easily angered
4: a deep thinker
4

Your significator is King of Pentacles

Please enter your question, to better influence the cards.
>Why are we here?

Shuffling...

This card crosses you.. it is your current main obstacle.
Three of Swords
This card is reversed...
Error, loss, distraction, confusion.
---Press a key---

----------------------------------------

=============
File Transfer
=============

File transfer was designed to be built and loaded as a door game from the
FILES;C module. It's *very* simple and offers XMODEM upload and download only.

There is very little here because FlipSide was a floppy based system and
had very little space for file transfers. The drive is hard coded to drive
'4' in XMODEM2 (look for "*DRIVE 4 (TEMP)").

----------------------------------------
Flip Side file transfers
------------------------
1 - View file listing
2 - Upload a file
3 - Download a file
4 - see info about this area
0 - return to online menu
----------------------------------------

View file listing dumps the file 'FILES' to the user. It's intended that the
sysop would have this contain a list of files and descriptions.

Upload a file allows a user to upload. Filenames must meet TI specifications,
which are only slightly checked before being tried.

----------------------------------------
Enter name of file being uploaded.
Must be 10 characters or less,
no punctuation, including period.
(ex: PIC/GIF instead of PIC.GIF)
>GAME@
Use CRC error checking? [Y]/n Yup!

Ready to receive file. Control-x aborts.
----------------------------------------

Download is similar, even the text is the same. The user must enter a valid
filename (which need not be listed in FILES). Thus they can get any file on
DSK4.

During transfer, the screen is used as a sector buffer, so you can see the
transfer take place. One sector at a time is processed.

See Info about this area dumps the file FILEINFO.

Return to Online menu reloads DOR for the online menu.
