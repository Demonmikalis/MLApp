#----------------------------------------------------------
#         Copyright: MR.Black <demonmikalis@google.com>
#         2018-2019 Engineering Department
#                   
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
LDFLAGS = -L/usr/X11R6/lib 
LIBS = -lm 
RANLIB = ranlib

# build rules
all: main


object = main.o Queue.o MinHeap.o LinkList.o HashMap.o HashSet.o HMem.o HMath.o \
HShell.o MathInterf.o Stack.o

objectLib = Queue.o MinHeap.o LinkList.o HashMap.o HashSet.o HMem.o HMath.o \
HShell.o MathInterf.o Stack.o

main: $(object) 
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS) 

CLib.a: $(objectLib)
	ar rv $@ $^
	$(RANLIB) $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o main

.PHONY: all

