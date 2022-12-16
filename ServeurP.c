#include "include/serv_cli_fifo.h"
#include "include/Handlers_Serv.h"
#include <string.h>
void hand_endServ(int sig)
{
  printf("arret du serveur ");
  exit(0);
}

int main()
{
  /*Déclarations */
  request req;
  response resp;
  int fdreq, fdrep;
  int out = open("SPIPE.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  dup2(out, 1);
  printf("Demarrage...");
  write(out, "Demarrage...", strlen("Demarrage..."));

  /* Création des tubes nommés */
  mkfifo(fifo1, 0666);
  mkfifo(fifo2, 0666);
  /*initialisation du générateur de nombres aléatoires*/
  srand(getpid());
  /* Ouverture des tubes nommés */
  fdreq = open(fifo1, O_RDONLY);
  fdrep = open(fifo2, O_WRONLY);

  /* Installation des Handlers */
  signal(SIGUSR1, hand_endServ);
  signal(SIGILL, hand_endServ);
  while (1)
  {
    /* lecture d’une question */

    read(fdreq, &req, sizeof(struct request));
    close(fdreq);
    /* construction de la réponse */
    for (int i = 0; i < req.n; i++)
    {
      resp.tab[i] = rand() % NMAX;
    }
    resp.pid = getpid();
    /* envoi de la réponse */

    write(fdrep, &resp, sizeof(response));
    close(fdrep);

    //   /* envoi du signal SIGUSR1 au client concerné */
    kill(req.pid, SIGUSR1);
    fdreq = open(fifo1, O_RDONLY);
    fdrep = open(fifo2, O_WRONLY);
  }

  return 0;
}