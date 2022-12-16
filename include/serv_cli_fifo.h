#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NMAX 10
char *fifo1 = "fifo1";
char *fifo2 = "fifo2";
// FIFO file path
// const char *fifo1 = "./fifo1";
// const char *fifo2 = "./fifo2";
// Creating the named file(FIFO)
int mode = S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH;
//  int prep = mkfifo(fifo2,S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH);

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
