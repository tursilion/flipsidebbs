19970508

FlipSide BBS was a BBS written from scratch for the TI-99/4A in Ottawa. I started it back in 1991 - originally as a terminal program, but it became a BBS pretty quickly. It was online from 1991 through 1995, then briefly in 1997 I tried to run it in Penticton BC... then a year or so later I tried one last time as a telnet BBS on the internet! But only in Ottawa did it really work.

Presented here is all the data I have remaining - there looks like enough to build it, but I certainly can't walk you through it. Originally it used Clint Pulley's c99, and the three letter files are the binary executables (my loader was written to only work with three letter filenames). Some of the data files remain. Looks like I created some documentation - check the readme in the dist folder.

I can tell you that it was meant to run through a Horizon RAMdisk, with FSL replacing the MENU program for auto-boot. The rest is largely configurable, though it's expected that message bases get their own disk drive number (as TI floppies are limited to 127 files). There is also code in there to use one of the cassette remotes to control the modem DTR line (and so provide a hardware disconnect), that requires a custom cable.

This is mostly presented as an artifact.