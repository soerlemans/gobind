#ifndef CGOBIND_H
#define CGOBIND_H

/*!
 * @file
 *
 * This header is utility header included by cgo.
 *
 */

// C Includes:
#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>

// Library Includes:
#include "gobind/gobind.h"

// TODO: Clean this shit up.

// RTLD_LAZY is a macro need to export by assigning it.
const int RTLD_LAZY_MODE = RTLD_LAZY;

//
typedef void* (*void_fn_ptr)(void);

//
typedef GobindModule* (*gobind_fn_ptr)(void);

void* call_void_func(void* t_func)
{
  return ((void_fn_ptr)t_func)();
}

GobindModule* call_gobind_module_init(void* t_func)
{
  return ((gobind_fn_ptr)t_func)();
}


#endif // CGOBIND_H
