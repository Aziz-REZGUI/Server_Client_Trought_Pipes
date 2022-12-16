CC=gcc
CFLAGS=-Wall -g
TARGET_C =client
TARGET_S=serveur
IDIR=
OBJ=

all : Client.o Serveur.o interface.o


Client.o :  
	$(CC) $(CFLAGS) Client.c -o $(TARGET_C)

Serveur.o : 
	$(CC) $(CFLAGS) Serveur.c -o $(TARGET_S)
interface.o : 
	$(CC) $(CFLAGS) -o Test interface.c `pkg-config --cflags --libs gtk+-3.0` -rdynamic

clean: 
	rm $(TARGET_C) 
	rm $(TARGET_S) 
	rm Test