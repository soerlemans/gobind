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
    GTYPE2STR(GTYPE_FLOAT, "float32");
    GTYPE2STR(GTYPE_DOUBLE, "float64");

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

const char* gtype2cgotype(GType t_gtype)
{
  const char* str = NULL;

 	// Void is no return type but when we return void*.
	// This should return a `unsafe.Pointer`.
  switch(t_gtype) {
    GTYPE2STR(GTYPE_VOID, "");
    GTYPE2STR(GTYPE_CHAR, "C.char");

    // Floating point:
    GTYPE2STR(GTYPE_FLOAT, "C.float");
    GTYPE2STR(GTYPE_DOUBLE, "C.double");

    // Integers:
    GTYPE2STR(GTYPE_SHORT, "C.short");
    GTYPE2STR(GTYPE_INT, "C.int");
    GTYPE2STR(GTYPE_LONG, "C.long");
    GTYPE2STR(GTYPE_LONG_LONG, "C.longlong");

    // Unsigned integers:
    GTYPE2STR(GTYPE_USHORT, "C.ushort");
    GTYPE2STR(GTYPE_UINT, "C.uint");
    GTYPE2STR(GTYPE_ULONG, "C.ulong");
    GTYPE2STR(GTYPE_ULONG_LONG, "C.ulonglong");

		// TODO: This must be implemented.
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
  }	/*  */

  return str;
}
