#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include "../serv_cli_fifo.h"
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd)
{
    request req;
    response resp;

    srand(getpid());
    req.n = rand() % NMAX;
    printf("la valeur choisis est %d\n", req.n);
    req.pid = getpid();
    write(sockfd, &req, sizeof(request));
    read(sockfd, &resp, sizeof(response));

    printf("la reponse est :\n");
    int i;
    for (i = 1; i < req.n; i++)
    {
        printf("%d, ", resp.tab[i]);
    }
    printf("%d", resp.tab[i + 1]);
    printf("\n");
}

int main()
{
    
    int sockfd;
    struct sockaddr_in servaddr;
    int out = open("CTCP.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(out, 1);

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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("erreur de connection avec le serveur...\n");
        exit(0);
    }
    else
        printf("connection établit..\n");

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}
