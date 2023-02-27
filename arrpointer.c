#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int (*ap)[10][10] = malloc(sizeof (*ap));
  printf("size int: %d\n", sizeof(int));
  printf("size ap: %d\n", sizeof (*ap));
  *ap[0][1] = 1;
  for (int i = 0; i < 10; i++)
    {
      for (int j = 0; j < 10; j++)
        {
          printf("element: %d\n", *ap[i][j]);
        }
    }
  return 0;
}
