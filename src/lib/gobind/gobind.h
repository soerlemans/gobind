#ifndef GOBIND_H
#define GOBIND_H

/*!
 * @file
 *
 * This header is intended to be included by cgo.
 * The headers suffixed with .h have a C API but a C++ implementation.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// Local Includes:
#include "gobind_module.h"

// Structs:
/*!
 * Contains the names of the registered modules.
 */
typedef struct {
  const char** m_modules;
  size_t m_size;
} GobindRegistery;

// Functions:
/*!
 * Very important function that returns the names of all modules.
 */
const GobindRegistery* gobind_registery(void);
void gobind_register_module(const char* t_name);

// Volatile Function Pointers:
//! Prevent @ref gobind_registery() from being optimized away by the compiler.
extern const GobindRegistery* (*volatile gobind_volatile_registery_ptr)(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // GOBIND_H
