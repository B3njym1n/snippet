#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); \
  } while (0)

static void sigintHandler(int sig)
{
  write(STDERR_FILENO, "Caught SIGINT\n", 15);
}

volatile sig_atomic_t stop;

void
inthand(int signum)
{
  stop = 1;
}

int main(int argc, char *argv[])
{
  /* If (signal(SIGINT, sigintHandler) == SIG_ERR) */
  /*   errExit("signal SIGiNT"); */

  /* while (1) {  not working  -_-|| */
  /*   fprintf(stderr, "%d", 0); */
  /*   sleep(3); */
  /* } */

  signal(SIGINT, inthand);

  while (!stop) {
    pause();
  }
  printf("exit safely\n");

  exit(EXIT_SUCCESS);
}
