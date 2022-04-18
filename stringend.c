#include <stdio.h>

int main() {
  char* str = "qwerty";
  short cnt = 0;
  while (*str != '\0') {
    printf("%c\t", *str);
    str++;
    cnt++;
  }
  printf("count: %d\n", cnt);
  return 0;
}
