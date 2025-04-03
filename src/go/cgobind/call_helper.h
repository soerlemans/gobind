#ifndef CALL_HELPER_H
#define CALL_HELPER_H

/*!
 * @file
 */

// Library Includes:
#include <gobind/gobind.h>

// Typedefs:
typedef void* (*void_fn_ptr)(void);
typedef GobindModule* (*gobind_fn_ptr)(void);

// Functions:
void* call_void_func(void* t_func)
{
  return ((void_fn_ptr)t_func)();
}

GobindModule* call_gobind_module_init(void* t_func)
{
  return ((gobind_fn_ptr)t_func)();
}

#endif // CALL_HELPER_H
