#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#define PORT 8080
#define SA struct sockaddr
#define NMAX 10
char *fifo1 = "fifo1";
char *fifo2 = "fifo2";

int mode = S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH;

// Structs

typedef struct request
{
	int pid;
	int n;
} request;

typedef struct response
{
	int pid;

	int tab[NMAX];
} response;
