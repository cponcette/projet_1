#
# Makefile projet 1 Systeme Informatique
# make : complie test.c et dames.c
#
CC	= gcc
LIBS	= -lcunit -I$(HOME)/local/include/CUnit -L$(HOME)/local/lib
all :	projet
#
projet : programme.c test.c dames.h aux.h
	$(CC) -std=c99 programme.c test.c 
#
jeu : programme.c dames.c dames.h aux.h
	$(CC) -std=c99 programme.c dames.c -o programme
#
test : test.c dames.c dames.h aux.h
	$(CC) -std=c99 dames.c test.c  $(LIBS)
clean :
	rm -rf *.o
