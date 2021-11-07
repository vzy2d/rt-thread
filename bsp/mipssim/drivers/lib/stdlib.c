#include <rthw.h>
#include <rtconfig.h>

#ifdef USING_LINUX_GNU_TOOLCHAIN

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}

unsigned long __stack_chk_guard;
void __stack_chk_guard_setup(void)
{
     __stack_chk_guard = 0xABCDDCBA;
}

void __stack_chk_fail(void)                         
{
 /* Error message */                                 
}

#endif