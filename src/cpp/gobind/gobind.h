#ifndef GOBIND_H
#define GOBIND_H

/*!
 * @file
 *
 * This header is intended to be included by cgo.
 * The headers suffixed with .h have a C API but a C++ implementation.
 */

#include "golang_module.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// Functions:
//! Very important function that returns all modules defined
GolangModule* gobind_modules();
void gobind_register_function();
void gobind_get_function();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // GOBIND_H
