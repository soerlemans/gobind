#include "gobind_type.h"

// STL Includes:
#include <cstring>
#include <sstream>

// Macros:
#define GTYPE2STR(t_gtype, t_str) \
  case t_gtype:                   \
    str = t_str;                  \
    break

// Functions:
const char* gtype2str(const GType t_gtype)
{
  const char* str{nullptr};

  switch(t_gtype) {
    GTYPE2STR(GTYPE_VOID, "void");
    GTYPE2STR(GTYPE_CHAR, "char");

    // Floating point:
    GTYPE2STR(GTYPE_FLOAT, "float");
    GTYPE2STR(GTYPE_DOUBLE, "double");

    // Integers:
    GTYPE2STR(GTYPE_SHORT, "short");
    GTYPE2STR(GTYPE_INT, "int");
    GTYPE2STR(GTYPE_LONG, "long");
    GTYPE2STR(GTYPE_LONG_LONG, "long long");

    // Unsigned integers:
    GTYPE2STR(GTYPE_USHORT, "unsigned short");
    GTYPE2STR(GTYPE_UINT, "unsigned int");
    GTYPE2STR(GTYPE_ULONG, "unsigned long");
    GTYPE2STR(GTYPE_ULONG_LONG, "unsigned long long");

    // Fixed width integers:
    GTYPE2STR(GTYPE_INT8, "int8_t");
    GTYPE2STR(GTYPE_INT16, "int16_t");
    GTYPE2STR(GTYPE_INT32, "int32_t");
    GTYPE2STR(GTYPE_INT64, "int64_t");

    // Fixed width unsigned integers:
    GTYPE2STR(GTYPE_UINT8, "int8_t");
    GTYPE2STR(GTYPE_UINT16, "int16_t");
    GTYPE2STR(GTYPE_UINT32, "int32_t");
    GTYPE2STR(GTYPE_UINT64, "int64_t");

    default:
      str = "UNKNOWN";
      break;
  }

  return str;
}

Error gobindtype2str(GobindType* t_gobind_type, char* t_buf,
                     const size_t t_size)
{
  Error error{};

  std::stringstream ss{};

  auto& gobind_type{*t_gobind_type};
  if(gobind_type.m_constant) {
    ss << "const ";
  }

  ss << gtype2str(gobind_type.m_type);


  const auto pointer_count{gobind_type.m_pointer};
  if(pointer_count > 0) {
    ss << " ";
  }

  for(auto index{0}; index < pointer_count; index++) {
    ss << "*";
  }

  const auto str_buf{ss.str()};

  // Check if the dest buffer has enough space for.
  // The string and NULL terminator.
  if(str_buf.size() >= t_size) {
    // Set error message for not a full copy.
    error_fail(&error, ERRORMSG_TOO_LONG_GTYPE_STR);
  }

  std::strncpy(t_buf, str_buf.c_str(), t_size);
  t_buf[t_size - 1] = '\0';

  return error;
}
