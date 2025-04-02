#ifndef ALLOC_HPP
#define ALLOC_HPP

// STL Includes:
#include <cstdlib>

namespace gobind {
/*!
 * Slightly more ergonomic definition of malloc.
 * Used in C++ code where we need to provide a C api.
 */
template<typename T>
inline auto malloc(const std::size_t t_capacity = 1) -> T*
{
  const auto size{sizeof(T) * t_capacity};

  return (T*)std::malloc(size);
}
} // namespace gobind

#endif // ALLOC_HPP
