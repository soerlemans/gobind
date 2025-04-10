#ifndef ALLOC_HPP
#define ALLOC_HPP

// STL Includes:
#include <cstdlib>
#include <iostream>
#include <cassert>

namespace gobind {
/*!
 * Slightly more ergonomic definition of malloc.
 * Used in C++ code where we need to provide a C api.
 */
template<typename T>
inline auto malloc(const std::size_t t_capacity = 1) -> T*
{
  const auto size{sizeof(T) * t_capacity};

  assert(size != 0 && "Error: gobind::malloc() size == 0.");

  return (T*)std::malloc(size);
}
} // namespace gobind

#endif // ALLOC_HPP
