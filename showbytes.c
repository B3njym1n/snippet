#include <stdio.h>

void show_bytes(void *start, size_t len)
{
  size_t i;
  for (i= 0; i< len; i++)
    {
      printf("%.2x ",*(unsigned char*)(start+i));
    }
  printf("\n");
}

int main()
{
  short x = 0x1234;
  short y = -0x1234;
  show_bytes(&x, sizeof(x));
  show_bytes(&y, sizeof(y));
  int x1 = x;
  int y1 = y;
  show_bytes(&x1, sizeof(x1));
  show_bytes(&y1, sizeof(y1));
}
