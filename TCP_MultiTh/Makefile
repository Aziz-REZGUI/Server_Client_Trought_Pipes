CC=gcc
CFLAGS=-Wall -g
TARGET_C =client
TARGET_S=serveur
IDIR=
OBJ=

all : Client.o Serveur.o


Client.o :  
	$(CC) $(CFLAGS) Client.c -o $(TARGET_C)

Serveur.o : 
	$(CC) $(CFLAGS) Serveur.c -o $(TARGET_S)

clean: 
	rm $(TARGET_C) 
	rm $(TARGET_S) 