#include "gtype2golang.h"

// Macros:
#define GTYPE2STR(t_gtype, t_str) \
  case t_gtype:                   \
    str = t_str;                  \
    break

// Functions:
const char* gtype2golang(GType t_gtype)
{
  const char* str = NULL;

  switch(t_gtype) {
    GTYPE2STR(GTYPE_VOID, "");
    GTYPE2STR(GTYPE_CHAR, "byte");

    // Floating point:
    GTYPE2STR(GTYPE_FLOAT, "float");
    GTYPE2STR(GTYPE_DOUBLE, "double");

    // Integers:
    GTYPE2STR(GTYPE_SHORT, "int");
    GTYPE2STR(GTYPE_INT, "int");
    GTYPE2STR(GTYPE_LONG, "int");
    GTYPE2STR(GTYPE_LONG_LONG, "int");

    // Unsigned integers:
    GTYPE2STR(GTYPE_USHORT, "int");
    GTYPE2STR(GTYPE_UINT, "int");
    GTYPE2STR(GTYPE_ULONG, "int");
    GTYPE2STR(GTYPE_ULONG_LONG, "int");

    // Fixed width integers:
    GTYPE2STR(GTYPE_INT8, "int");
    GTYPE2STR(GTYPE_INT16, "int");
    GTYPE2STR(GTYPE_INT32, "int");
    GTYPE2STR(GTYPE_INT64, "int");

    // Fixed width unsigned integers:
    GTYPE2STR(GTYPE_UINT8, "int");
    GTYPE2STR(GTYPE_UINT16, "int");
    GTYPE2STR(GTYPE_UINT32, "int");
    GTYPE2STR(GTYPE_UINT64, "int");

    default:
      str = "UNKNOWN";
      break;
  }

  return str;
}
