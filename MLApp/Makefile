#----------------------------------------------------------
#         Copyright: MR.Black <demonmikalis@google.com>
#         2018-2019 Engineering Department
#         Main Make File For Machine Learning App         
#                   
#                 
#   Use of this software is governed by a License Agreement   
#    ** See the file License for the Conditions of Use  **    
#    **     This banner notice must not be removed      **    
#                                                             
# ----------------------------------------------------------- 
# File: Makefile.  Generated from Makefile.in by configure.
# ----------------------------------------------------------- 


CC = gcc
CPPFLAGS = 
#CFLAGS = $(CPPFLAGS)  -ansi -D_SVID_SOURCE -DOSS_AUDIO -D'ARCH="x86_64"' -Wall -Wno-switch -g -O2 -DNO_LAT_LM
CFLAGS = -Wall -g
LDFLAGS = -L/usr/X11R6/lib CLib/CLib.a -lm
LIBS = -lm 
RANLIB = ranlib
INC = CLib/

# build rules
all: CLibMake CLib main

CLibMake:
	(cd CLib && $(MAKE) CLib.a)

CLib: CLib/CLib.a
	

object = main.o Expression.o GoBangAI.o RegTrees/DecisionTree.o


main: $(object) $(CLib)
	$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS)


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 

RegTrees/DecisionTree.o: RegTrees/DecisionTree.c
	$(CC) $(CFLAGS) -c -o $@ $< 

clean:
	rm *.o main 

.PHONY: all

