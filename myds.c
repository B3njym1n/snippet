#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include <stdio.h>

typedef struct VECT {
  double x;
  double y;
} vect;

vect
make_vect(double x, double y)
{
  vect v;
  v.x = x;
  v.y = y;
  return v;
}

int main(void) {
  vect* arr = NULL;

  arrput(arr, make_vect(1,2));
  arrput(arr, make_vect(2,2));
  arrput(arr, make_vect(3,2));
  arrput(arr, make_vect(4,2));
  arrput(arr, make_vect(5,2));

  for (int i = 0; i < arrlen(arr); i++) {
    printf("%5.2f %5.2f\n", arr[i].x, arr[i].y);
  }

  return 0;
}
