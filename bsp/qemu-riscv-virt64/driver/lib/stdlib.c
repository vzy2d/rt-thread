#include <rthw.h>
#include <rtconfig.h>

#ifdef USING_RV64_LINUX_GNU_TOOLCHAIN

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}

static unsigned long int next = 1;

int rand(void) {
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}
int exit(int id){
  return 0;
}

#endif