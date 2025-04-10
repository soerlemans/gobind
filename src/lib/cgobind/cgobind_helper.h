#ifndef CGOBIND_HELPER_H
#define CGOBIND_HELPER_H

/*!
 * @file
 *
 * This file is intended to be used by the gobind command cgobind package.
 * In here is everything needed for 
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

#endif // CGOBIND_HELPER_H
