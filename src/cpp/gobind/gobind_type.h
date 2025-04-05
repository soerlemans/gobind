#ifndef GOBIND_TYPE_H
#define GOBIND_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// C Includes:
#include <stdbool.h>
#include <stdlib.h>

// Local Includes:
#include "error.h"

// Macros:
/*!
 * This is enough space for "const unsigned long long" (28).
 * And a ton of pointer indirection.
 * This value is intended as a guideline unless you have an insanely long type.
 * Which is supported by Gobind in the @ref GType enum.
 */
#define GOBIND_TYPE_MAX_STR_LENGTH (256)

#define ERRORMSG_TOO_LONG_GTYPE_STR \
  ("Not enough space in buffer for storing gtype string.")

// Enums:
/*!
 * List of all supported C/C++ types.
 * Used for encoding into @ref GobindFunction.
 * That way we can generate function signatures for the golang templates.
 */
enum GType {
  // Misc:
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

// Functions:
const char* gtype2str(GType t_gtype);
Error gobindtype2str(GobindType* t_gobind_type, char* t_buf, size_t t_size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // GOBIND_TYPE_H
