#ifndef GOLANG_FUNCTION_TABLE_H
#define GOLANG_FUNCTION_TABLE_H

/*!
 * @file
 *
 *
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// C Includes:
#include <stddef.h>

// Local Includes:
#include "error.h"

// Macros:
#define GOBIND_FUNCTION_TABLE_DEFAULT_CAPACITY_SIZE (10)

// EGB is short for Error Gobind.
#define EGB_FUNCTION_TABLE_BAD_ALLOC ("std::realloc() has failed.")
#define EGB_FUNCTION_TABLE_BAD_STATE ("Bad state size exceeds capacity.")

// Typedefs:
//! Void function pointer type, intended to be cast later.
typedef void (*VoidFnPtr)(void);

// Structs:
typedef struct {
  const char* m_name;
  VoidFnPtr m_fn;
  // TODO: Insert Enum field for return type.
  // TODO: Insert Enum array field for parameters.
  // CppType m_return_type;
  // CppType* m_params;
  // size_t m_params_size;
} GobindFunction;

/*!
 * Function table consisting function pointers that will be exported to Golang.
 */
typedef struct {
  GobindFunction* m_functions;
  size_t m_size;
  size_t m_capacity;
} GobindFunctionTable;

// Functions:
Error gobind_function_table_create(GobindFunctionTable** t_fn_table,
                                   size_t t_size);
Error gobind_function_table_add(GobindFunctionTable** t_fn_table,
                                GobindFunction* t_function);
void gobind_function_table_free(GobindFunctionTable** t_fn_table);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // GOLANG_FUNCTION_TABLE_H
