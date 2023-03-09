#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 128

int main()
{
  char buf[BUFSIZE];
  char *str = "lalalalalalala";

  strncpy(buf, str, strlen(str));
  printf("buf:\n%s\n\n", buf);

  int a1[10], a2[100], i;
  for (i = 0; i < 100; i++)
    {
      a2[i] = i*i;
    }
  memcpy_s(a1, sizeof(a1), a2, 10*sizeof(int));
  if (err)
    {
      printf("error executing memcpy_s.\n");
    }
  else
    {
      for(i = 0; i<10;i++)
        {
          printf("%d ", a1[i]);
        }
      printf("\n");
    }
  return 0;
}
