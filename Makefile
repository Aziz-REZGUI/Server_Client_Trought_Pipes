CC=gcc
CFLAGS=
TARGET_C =client
TARGET_S=serveur
IDIR=
OBJ=

all:interface.o  Client.o Serveur.o 
interface.o : 
	$(CC) $(CFLAGS) -o Final interface.c `pkg-config --cflags --libs gtk+-3.0` -rdynamic
Client.o :  
	$(CC) $(CFLAGS) ClientSK.c -o clientSK
	$(CC) $(CFLAGS) ClientP.c -o clientP
	touch CTCP.txt
	touch CPIPE.txt

Serveur.o : 
	$(CC) $(CFLAGS) ServeurSK.c -o serveurSK
	$(CC) $(CFLAGS) ServeurP.c -o serveurP
	touch STCP.txt
	touch SPIPE.txt

clean: 
	rm Final
	rm $(TARGET_C)* 
	rm $(TARGET_S)* 
	rm fifo*
	rm *.txt