#include <stdio.h>

#define crBegin static int state=0; switch(state) { case 0:
/* #define crReturn(i, x) do {state=i; return x; case i:;} while (0) */
#define crReturn(i, x) do {state=__LINE__; return x; case __LINE__:;} while (0)
#define crFinish }

int function(void) {
  static int i, state = 0;
  switch (state) {
    case 0: /* start of the function */
    for (i = 0; i < 10; i++) {
      state = 1;
      return i;
    case 1:;
    }
  }
}

int function2(void) {
  static int i;
  crBegin;
  for (i = 0; i < 10; i++) 
    crReturn(1, i);
  crFinish;
}

int main()
{
  int r;
  for (int c = 0; c < 18; ++c) {
    r = function2();
    printf("%d\n", r);
  }
  return 0;
}
