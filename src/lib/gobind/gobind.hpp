#ifndef GOBIND_HPP
#define GOBIND_HPP

/*!
 * @file
 *
 * C++ API for registering the C++ functions for cgo to import later.
 */

// STL Includes:
#include <cassert>
#include <exception>
#include <iostream>
#include <string_view>

// Local Includes:
#include "gobind_module_factory.hpp"
#include "macros.h"

// Macros:
//! Create a name for internal usage by gobind.
#define GOBIND_INTERNAL(t_name, t_module_name) \
  GOBIND_CONCAT(gobind_##t_name##_, t_module_name)

// TODO: Fix lazy assert error message.
// FIXME: For now we discard the result of factory.create_module().

/*!
 * Define a @ref GobindModule that can be included from Golang.
 * This module defines two functions:
 *
 * gobind_struct_init_hook_* # Struct
 * gobind_init_*() # Function
 * gobind_populate_*() # Function
 *
 * The struct is used for invoking the
 *
 * @note We call valid_module_name() in gobind_init_*().
 * As we then check it at compile time (potentially).
 */
#define GOBIND_MODULE(t_name, t_param)                                  \
  extern "C" GobindModule* GOBIND_INTERNAL(init, t_name)(void);         \
  void GOBIND_INTERNAL(populate, t_name)(gobind::GobindModuleFactory&); \
  struct GOBIND_INTERNAL(struct_init_hook, t_name) {                    \
    GOBIND_INTERNAL(struct_init_hook, t_name)()                         \
    {                                                                   \
      gobind_register_module(#t_name);                                  \
    }                                                                   \
  };                                                                    \
  GOBIND_INTERNAL(struct_init_hook, t_name)                             \
  GOBIND_INTERNAL(var_init_hook, t_name);                               \
  extern "C" GobindModule* GOBIND_INTERNAL(init, t_name)(void)          \
  {                                                                     \
    using gobind::GobindModuleFactory;                                  \
    using gobind::valid_module_name;                                    \
    GobindModuleFactory factory{};                                      \
    try {                                                               \
      const auto error{valid_module_name(#t_name)};                     \
      error_assert(&error);                                             \
      factory.create_module(#t_name);                                   \
      GOBIND_INTERNAL(populate, t_name)(factory);                       \
      factory.compile_module();                                         \
    } catch(std::exception & e) {                                       \
      std::cerr << "Error: " << e.what() << '\n';                       \
      std::exit(ERROR_FAIL);                                            \
    }                                                                   \
    return factory.get_module();                                        \
  }                                                                     \
  auto GOBIND_INTERNAL(populate,                                        \
                       t_name)(gobind::GobindModuleFactory & t_param) -> void

// END GOBIND_MODULE.

namespace gobind {}

#endif // GOBIND_HPP
