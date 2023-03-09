#include <stdio.h>
#include <stdlib.h>

int main()
{
  printf("size of void* : %u\n", sizeof(void*));
  void **p = (void**) malloc(sizeof(void*)*8);
  char s[] = "hello";
  size_t i;
  for (i =0; i<8;i++)
    {
      p[i] = s;
      printf("p[%u]: %s\n", i, p[i]);
    }
  free(p);
  return 0;
}
