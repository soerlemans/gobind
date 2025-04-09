#include "cgobind.h"

// Functions:
void* dlopen_lazy(const char* t_filename)
{
  return dlopen(t_filename, RTLD_LAZY);
}
