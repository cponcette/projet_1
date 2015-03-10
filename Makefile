#
# Makefile projet 1 Systeme Informatique
# make : complie test.c et dames.c
#
CC	= gcc
LIBS	= -lcunit -I$(HOME)/local/include -L$(HOME)/local/lib
all :	projet
#
projet : programme.c test.c dames.h aux.h
	$(CC) programme.c test.c 
#
jeu : programme.c dames.c dames.h
	$(CC) programme.c dames.c -o programme
#
test :  dames.c test.c dames.h aux.h 
	$(CC) -c test.c  -o test $(LIBS)
clean :
	rm -rf *.o
 
