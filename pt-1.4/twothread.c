/* We must always include pt.h in our protothreads code. */
#include "pt.h"

#include <stdio.h> /* For printf(). */

/* Two flags that the two protothread functions use. */
static int protothread1_flag, protothread2_flag;

static int
protothread1(struct pt *pt)
{
  /* A protothread function must begin with PT_BEGIN() which takes a
     pointer to a struct pt. */
  PT_BEGIN(pt);

  /* We loop forever here. */
  while(1) {
    /* Wait until the other protothread has set its flag. */
    PT_WAIT_UNTIL(pt, protothread2_flag != 10);
    printf("Protothread 1 running\n");

    /* We then reset the other protothread's flag, and set our own
       flag so that the other protothread can run. */
    /* protothread2_flag = 0; */
    protothread2_flag += 1;
    /* protothread1_flag = 1; */
    if (protothread2_flag == 10) {
      protothread1_flag = 1;
    }

    /* And we loop. */
  }

  /* All protothread functions must end with PT_END() which takes a
     pointer to a struct pt. */
  PT_END(pt);
}

/**
 * The second protothread function. This is almost the same as the
 * first one.
 */
static int
protothread2(struct pt *pt)
{
  PT_BEGIN(pt);

  while(1) {
    /* Let the other protothread run. */
    protothread2_flag = 1;

    /* Wait until the other protothread has set its flag. */
    PT_WAIT_UNTIL(pt, protothread1_flag != 0);
    printf("Protothread 2 running\n");
    
    /* We then reset the other protothread's flag. */
    protothread1_flag = 0;

    /* And we loop. */
  }
  PT_END(pt);
}

static
PT_THREAD(driver_thread(struct pt *pt))
{
  static struct pt pt1, pt2;

  PT_BEGIN(pt);
  PT_INIT(&pt1);
  PT_INIT(&pt2);

  PT_WAIT_THREAD(pt, protothread1(&pt1) & protothread2(&pt2));
  PT_END(pt);
}

int
main(void)
{
  struct pt driver_pt;
  while (PT_SCHEDULE(driver_thread(&driver_pt))) {
    
  }
  return 0;
}
