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
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Local Includes:
#include "call_helper.h"

// Functions:
//! Helper that uses RTLD_LAZY.
void* dlopen_lazy(const char* t_filename)
{
  return dlopen(t_filename, RTLD_LAZY);
}

#endif // CGOBIND_H
