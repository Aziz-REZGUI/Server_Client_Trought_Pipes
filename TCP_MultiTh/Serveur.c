#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h> // read(), write(), close()
#include "../serv_cli_fifo.h"
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int connfd)
{
  request req;
  response resp;

  srand(getpid());

  // read the message from client and copy it in buffer
  read(connfd, &req, sizeof(struct request));
  printf("le client a evoyé %d\n", req.n);

  for (int i = 0; i < req.n; i++)
  {
    resp.tab[i] = rand() % NMAX;
  }
  resp.pid = getpid();

  write(connfd, &resp, sizeof(response));

  kill(getpid(), SIGKILL);
}

// Driver function
int main()
{
  int sockfd, connfd;
  struct sockaddr_in servaddr, cli;
  socklen_t len;

  // socket create and verification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    printf("erreur dans la création du soket...\n");
    exit(0);
  }
  else
    printf("création du socket avec succées..\n");
  bzero(&servaddr, sizeof(servaddr));

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  // Binding newly created socket to given IP and verification
  if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
  {
    printf("erreur du binding..\n");
    exit(0);
  }
  else
    printf("Binding avec succées..\n");

  // Now server is ready to listen and verification
  if ((listen(sockfd, 5)) != 0)
  {
    printf("erreur d'écoute..\n");
    exit(0);
  }
  else
    printf("Le serveur est en train d'écoute..\n");
  len = sizeof(struct sockaddr_in);
  // Accept the data packet from client and verification

  int pid;

  while (1)
  {
    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
      printf("ecceur d'accéptation ...\n");
      exit(0);
    }
    else
      printf("accéptation avec succées...\n");
    pid = fork();
    if (pid < 0)
    {
      perror("erreur de creation du nouveau porcess");
      exit(1);
    }
    else
    {
      if (pid == 0)
      { // Function for chatting between client and server
        close(sockfd);

        func(connfd);
        close(connfd);
      }
      else
      {
        close(connfd);
      }
    }
  }
  return 0;
}
