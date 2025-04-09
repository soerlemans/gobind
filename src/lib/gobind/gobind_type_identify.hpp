#ifndef GOBIND_TYPE_ID_HPP
#define GOBIND_TYPE_ID_HPP

// STL Includes:
#include <array>
#include <cstdint>
#include <exception>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <type_traits>

// Local Includes:
#include "gobind_type.h"

namespace gobind {
// Globals:
// Type alias to simplify is_same_v usage
template<class T, class U>
constexpr bool eq = std::is_same<T, U>::value;

// Functions:
//! Recursively detect the amount of pointer indirection.
template<typename T>
constexpr auto pointer_depth() -> int
{
  if constexpr(std::is_pointer_v<T>) {
    return pointer_depth<std::remove_pointer_t<T>>() + 1;
  } else {
    return 0;
  }
}

/*!
 * Convert a given type too a @ref GType.
 * @throw std::invalid_argument When an unsupported type is received.
 */
template<typename T>
auto detect_type() -> GType
{

  GType type{GTYPE_VOID};

  // Misc:
  if constexpr(eq<T, void>) {
    type = GTYPE_VOID;
  } else if constexpr(eq<T, char>) {
    type = GTYPE_CHAR;

    // Floating point:
  } else if constexpr(eq<T, float>) {
    type = GTYPE_FLOAT;
  } else if constexpr(eq<T, double>) {
    type = GTYPE_DOUBLE;

    // Integers:
  } else if constexpr(eq<T, short>) {
    type = GTYPE_SHORT;
  } else if constexpr(eq<T, int>) {
    type = GTYPE_INT;
  } else if constexpr(eq<T, long>) {
    type = GTYPE_LONG;
  } else if constexpr(eq<T, long long>) {
    type = GTYPE_LONG_LONG;

    // Unsigned integers:
  } else if constexpr(eq<T, unsigned short>) {
    type = GTYPE_USHORT;
  } else if constexpr(eq<T, unsigned int>) {
    type = GTYPE_UINT;
  } else if constexpr(eq<T, unsigned long>) {
    type = GTYPE_ULONG;
  } else if constexpr(eq<T, unsigned long long>) {
    type = GTYPE_ULONG_LONG;

    // Fixed width integers:
  } else if constexpr(eq<T, int8_t>) {
    type = GTYPE_INT8;
  } else if constexpr(eq<T, int16_t>) {
    type = GTYPE_INT16;
  } else if constexpr(eq<T, int32_t>) {
    type = GTYPE_INT32;
  } else if constexpr(eq<T, int64_t>) {
    type = GTYPE_INT64;

    // Fixed width unsigned integers:
  } else if constexpr(eq<T, uint8_t>) {
    type = GTYPE_UINT8;
  } else if constexpr(eq<T, uint16_t>) {
    type = GTYPE_UINT16;
  } else if constexpr(eq<T, uint32_t>) {
    type = GTYPE_UINT32;
  } else if constexpr(eq<T, uint64_t>) {
    type = GTYPE_UINT64;
  } else {
    std::stringstream ss{};

    const auto unsupported_type{typeid(T).name()};

    ss << "Unsupported type ";
    ss << std::quoted(unsupported_type);
    ss << ".";

    throw std::invalid_argument{ss.str()};
  }

  return type;
}

template<typename T>
constexpr auto sym_identify() -> GobindType
{
  using NoPtrBaseType = std::remove_pointer_t<T>;
  using BaseType = std::remove_cv_t<NoPtrBaseType>;

  GobindType type{};
  type.m_constant = std::is_const_v<NoPtrBaseType>;
  type.m_type = detect_type<BaseType>();
  type.m_pointer = pointer_depth<T>();

  return type;
}

template<typename... Args>
constexpr auto args_identify()
{
  constexpr std::size_t count{sizeof...(Args)};

  std::array<GobindType, count> array{sym_identify<Args>()...};

  return array;
}

} // namespace gobind

#endif // GOBIND_TYPE_ID_HPP
