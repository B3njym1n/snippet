#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void) {

  int loop_flag = 1;
  int i = 0;
  srand(time(NULL));
  while (loop_flag) {
    printf("%d %d\n", i, rand() % 9);
    i += 2;
  }
  exit(EXIT_SUCCESS);
}
