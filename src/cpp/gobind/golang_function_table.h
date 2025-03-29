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
} GolangFunction;

/*!
 * Function table consisting function pointers that will be exported to Golang..
 */
typedef struct {
  GolangFunction* m_entries;
  size_t m_size;
} GolangFunctionTable;

Error golang_function_table_create(GolangFunctionTable** t_fn_table,
                                   size_t t_size);
void golang_function_table_free(GolangFunctionTable** t_fn_table);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // GOLANG_FUNCTION_TABLE_H
