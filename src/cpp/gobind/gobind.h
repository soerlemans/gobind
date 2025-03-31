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
#include "golang_module.h"

// Structs:
/*!
 * Contains registered @ref GolangModule.
 * From this function the gobind command tool.
 * Retrieves all the @ref GobindModules.
 * Which it uses to generate its source code.
 */
typedef struct {
  const GolangModule* m_modules;
  size_t m_size;
} GobindModules;

// Functions:
/*!
 * Very important function that returns all modules defined.
 */
volatile const GobindModules* gobind_registered_modules();
void gobind_register_module(GolangModule* t_module);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // GOBIND_H
