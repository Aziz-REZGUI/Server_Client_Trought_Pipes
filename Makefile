CC=gcc
CFLAGS=-Wall -g
DEPS=Handlers_cli.h Handlers_Serv.h serv_cli_fifo.h
TARGET =
IDIR=
OBJ=

all : Client.o Serveur.o

$(TARGET) :

Client.o : $(IDIR)Client.c
	$(CC) $(CFLAGS) -c $(IDIR)Client.c -o Client.o

Serveur.o : $(IDIR)Serveur.c
	$(CC) $(CFLAGS) -c $(IDIR)Serveur.c -o Serveur.o

clean:
	rm fifo* 
	rm *.o