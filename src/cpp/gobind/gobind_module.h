#ifndef GOLANG_MODULE_HPP
#define GOLANG_MODULE_HPP

/*!
 * @file
 *
 * This file contains the @ref GolangModule struct what is the data structure.
 * Used to communicate the function pointers/bindings to Go.
 * This must be C compatible as Golang only has C compatibility via Cgo.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// Local Includes:
#include "error.h"
#include "gobind_function_table.h"

// Constants:
#define GOBIND_MODULE_MAX_NAME_LENGTH (256)

#define ERRORMSG_INVALID_GOBIND_MODULE_NAME ("Invalid Golang Module name.")

// Structs:
typedef struct {
  const char* m_name;
  GobindFunctionTable* m_fn_table;
} GobindModule;

// Functions:
Error gobind_module_create(GobindModule** t_module, const char* t_name);
void gobind_module_invalid_name(const char* t_name);
// Error gobind_module_add_function(GobindModule* t_module, );
// Error gobind_module_add_struct(GobindModule* t_module, );
void gobind_module_free(GobindModule** t_module);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // GOLANG_MODULE_HPP
