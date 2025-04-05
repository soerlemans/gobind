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
typedef const char* (*cstr_fn_ptr)(void);
typedef const char* (*gtype2str_fn_ptr)(GType);

// Functions:
void* call_void_func(void* t_func)
{
  return ((void_fn_ptr)t_func)();
}

GobindModule* call_gobind_module_init(void* t_func)
{
  return ((gobind_fn_ptr)t_func)();
}

const char* call_gtype2str(void* t_func, const GType t_type)
{
  return ((gtype2str_fn_ptr)t_func)(t_type);
}


#endif // CALL_HELPER_H
