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

// Library Includes:
#include <gobind/gobind.h>

// Functions:
//! Helper that uses RTLD_LAZY.
void* dlopen_lazy(const char* t_filename);

#endif // CGOBIND_H
