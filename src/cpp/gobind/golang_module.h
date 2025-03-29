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
#include "golang_function_table.h"

// Constants:
#define GOLANG_MODULE_MAX_NAME_LENGTH (256)

#define ERRORMSG_INVALID_GOLANG_MODULE_NAME ("Invalid Golang Module name.")

// Structs:
typedef struct {
  char m_name[GOLANG_MODULE_MAX_NAME_LENGTH];
  GolangFunctionTable* m_fn_table;
} GolangModule;

// Functions:
Error golang_module_create(GolangModule** t_module, const char* t_name);
// Error golang_module_add_function(GolangModule* t_module, );
// Error golang_module_add_struct(GolangModule* t_module, );
void golang_module_free(GolangModule** t_module);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // GOLANG_MODULE_HPP
