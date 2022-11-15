#include "serv_cli_fifo.h"
#include "Handlers_cli.h"

void hand_wakeUpClt(int sig)
{
    // Wake up
    printf("traitement de la reponse\n");
}
int main()
{
    //  printf("debug");
    /* Déclarations */
    request req;
    response resp;
    // char *fifo1 = "fifo1";
    // char *fifo2 = "fifo2";
    int fdreq, fdrep;
    /* Ouverture des tubes nommés */
    fdreq = open(fifo1, O_WRONLY);
    fdrep = open(fifo2, O_RDONLY);
    /* Installation des Handlers */
    signal(SIGUSR1, hand_wakeUpClt);

    /* Construction et envoi d’une question */
    srand(getpid());
    req.n = rand() % NMAX;
    req.pid = getpid();
    // printf("n %d PID %d\n",req.n,req.pid);

    write(fdreq, &req, sizeof(request));

    close(fdreq);
    /* Attente de la réponse */
    pause();

    /* Lecture de la réponse */

    read(fdrep, &resp, sizeof(response));
    close(fdrep);

    /* Envoi du signal SIGUSR1 au serveur */
    kill(SIGUSR1, resp.pid);
    /* Traitement local de la réponse */
    printf("la reponse est :\n");
    int i;
    for (i = 0; i < req.n - 1; i++)
    {
        printf("%d, ", resp.tab[i]);
    }
    printf("%d", resp.tab[i + 1]);
    printf("\n");
    return 0;
}