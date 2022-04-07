#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mp.h"

#ifdef C89
#define HOPEFULLY_DECLARE_AS_INT(x)
int _i;
#else
#define HOPEFULLY_DECLARE_AS_INT(x) int x
#endif

#define MPCR_BEGIN switch(s->_line) { case 0:
#define MPCR_END(dummyval) s->_line = -1; }
#define MPCR_YIELD(value) do \
  {                         \
    s->_line = __LINE__;    \
    s->_val = (value);      \
    return;                 \
    case __LINE__:;         \
  } while (0)               \
/*
 * General test loops to exercise a lot of the macros.
 */
#define TEST_LOOP_1(loopvar, start, limit)        \
  MPP_DECLARE(1, HOPEFULLY_DECLARE_AS_INT(_i))    \
  MPP_BEFORE(2, printf("preloop\n"); _i = start)  \
  MPP_AFTER(3, printf("postloop\n"))              \
  MPP_WHILE(4, _i < limit)                        \
  MPP_BREAK_CATCH(5)                              \
  MPP_BEFORE(6, printf("preiter %d\n", _i))       \
  MPP_AFTER(7, printf("postiter %d\n", _i); _i++) \
  MPP_DECLARE(8, loopvar = _i + 100)              \
  MPP_BREAK_THROW(5)                              \
  MPP_BREAK_HANDLER(9, printf("break!\n"))        \
  MPP_FINALLY(10, printf("finally\n"))

/* Use with coroutines */
struct twothree_state {
  int _line, _val;
  int limit;
  int i;
};

typedef struct twothree_state STATE;

void twothree_iterator(STATE *s){
  int tmp;
  MPCR_BEGIN;
  for (s->i = 1; s->i < s->limit; s->i *= 2) {
    MPCR_YIELD(s->i);
    if (s->i > 1) {
      tmp = s->i + (s->i >>1);
      if (tmp < s->limit)
        MPCR_YIELD(tmp);
    }
  }
  MPCR_END(0);
}

#define TWOTHREE_UP_TO(loopvar, limitval) \
  MPP_DECLARE(1, STATE _state)            \
  MPP_BEFORE(2, _state._line = 0;         \
             _state.limit = limitval;     \
             twothree_iterator(&_state))  \
  MPP_WHILE(3, _state._line >= 0)         \
  MPP_BREAK_CATCH(4)                       \
  MPP_AFTER(5, twothree_iterator(&_state))\
  MPP_DECLARE(6, loopvar = _state._val)    \
  MPP_BREAK_THROW(4)                      

int main(void)
{
  /* int j; */
  /* TEST_LOOP_1(j, 0, 10) { */
  /*   printf("got %d\n", j); if (j == 103) break; */
  /* }  */
  TWOTHREE_UP_TO(int k, 1000) printf("%d\n", k);
}
