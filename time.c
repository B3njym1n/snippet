#include <stdio.h>
#include <time.h>

int main()
{
  time_t sec;
  sec = time(NULL);

  printf("Number of hours since Jan 1 1970 is %ld\n", sec/3600);

  /* print local time using ctime */
  printf(ctime(&sec));

  struct tm str_time;
  time_t time_of_day;

  str_time.tm_year = 2022-1900;
  str_time.tm_mon = 2;
  str_time.tm_mday = 5;
  str_time.tm_hour = 10;
  str_time.tm_min = 3;
  str_time.tm_sec = 5;
  str_time.tm_isdst = 0;

  time_of_day = mktime(&str_time);
  printf(ctime(&time_of_day));

  printf("The loop used %f seconds.\n", difftime(time(0), time_of_day));
  return 0;
}
