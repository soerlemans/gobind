#ifndef CGOBIND_WRAPPER_H
#define CGOBIND_WRAPPER_H

/*!
 * @file
 */

// Library Includes:
#include <gobind/gobind.h>

// Local Includes:
#include "cgobind.h"

// Functions:
void* call_void_func(void* t_func);
GobindRegistery* call_registered_modules(void* t_func);
GobindModule* call_gobind_module_init(void* t_func);
const char* call_gtype2str(void* t_func, const GType t_type);

#endif // CGOBIND_WRAPPER_H
