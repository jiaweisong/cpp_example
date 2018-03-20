#include <sys/time.h>
int64_t Time()
{
  timeval end;
  gettimeofday(&end, NULL);
  return end.tv_sec*1e6 + end.tv_usec;
}
