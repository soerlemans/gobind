#ifndef GOBIND_TYPE_ID_HPP
#define GOBIND_TYPE_ID_HPP

// STL Includes:
#include <exception>
#include <type_traits>

// Local Includes:
#include "gobind_type.h"

namespace gobind {
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

//! Detect the type.
template<typename T>
auto detect_type() -> GType
{
  GType type{};

  if constexpr(std::is_same_v<T, void>) {

  } else if constexpr(std::is_same_v<T, char>) {
  } else {
    throw std::invalid_argument{};
  }
}

// TODO: Use GobindFunction.
// template<typename Ret, typename... Args>
// auto function_identify() -> GobindType
// {}

template<typename T>
auto var_identify(T&& t_var) -> GobindType
{
  // FIXME: We need to account for reference types some day.
  using Decayed = std::decay_t<T>; // Remove references but keep const/ptr.
  using BaseType = std::remove_cv_t<std::remove_pointer_t<T>>;

  GobindType type{false, GTYPE_VOID, pointer_depth<T>()};

  // Check if it's a constant.
  if constexpr(std::is_const_v<std::remove_pointer_t<T>>) {
    type.m_constant = true;
  }

  return type;
}
} // namespace gobind

#endif // GOBIND_TYPE_ID_HPP
