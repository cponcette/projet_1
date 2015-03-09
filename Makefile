#
# Makefile projet 1 Systeme Informatique
# make : complie test.c et dames.c
#
CC	= gcc
#LIBS	= 
all :	projet
#
projet : test.o jeu.o
	$(CC) -o jeu.o test.o
#
tes.o : test.c dames.h dames.c
	$(CC) -c test.c 
#
jeu.o : programme.c dames.c dames.h
	$(CC) -c programme.c 
#
jeu : jeu.o
	$(CC) -o jeu.o -o programme
#
test : dames.h dames.c
	$(CC) -c test.c -o test
clean :
	rm -rf *.o

