#ifndef GOBIND_TYPE_H
#define GOBIND_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// C Includes:
#include <stdbool.h>

// Enums:
/*!
 * List of all supported C/C++ types.
 * Used for encoding into @ref GobindFunction.
 * That way we can generate function signatures for the golang templates.
 */
enum GType {
  GTYPE_VOID,
  GTYPE_CHAR,

  // Floating point:
  GTYPE_FLOAT,
  GTYPE_DOUBLE,

  // Integers:
  GTYPE_SHORT,
  GTYPE_INT,
  GTYPE_LONG,
  GTYPE_LONG_LONG,

  // Unsigned integers:
  GTYPE_USHORT,
  GTYPE_UINT,
  GTYPE_ULONG,
  GTYPE_ULONG_LONG,

  // Fixed width integers:
  GTYPE_INT8,
  GTYPE_INT16,
  GTYPE_INT32,
  GTYPE_INT64,

  // Fixed width unsigned integers:
  GTYPE_UINT8,
  GTYPE_UINT16,
  GTYPE_UINT32,
  GTYPE_UINT64
};

// Structs:
/*!
 * Used to keep track of the type of an entity.
 *
 * @note An int is used for m_pointer as there can be levels of indirection.
 */
struct GobindType {
  bool m_constant;
  GType m_type;
  int m_pointer;
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // GOBIND_TYPE_H
