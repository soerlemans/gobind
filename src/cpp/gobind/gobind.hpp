#ifndef GOBIND_HPP
#define GOBIND_HPP

/*!
 * @file
 *
 * C++ API for registering the C++ functions for cgo to import later.
 */

// STL Includes:
#include <cassert>
#include <iostream>
#include <string_view>

// Local Includes:
#include "golang_module_factory.hpp"
#include "macros.h"

// Macros:
//
#define GOBIND_INTERNAL_FN(t_name, t_module_name) \
  GOBIND_CONCAT(gobind_##t_name##_, t_module_name)

// TODO: Fix lazy assert error message.
// FIXME: For now we discard the result of factory.create_module().

/*!
 * Define a Golang module that can be included from Golang.
 * This module defines two functions:
 * gobind_init_*()
 * gobind_populate_*()
 *
 * @note We call valid_module_name() in gobind_init_*().
 * As we then check it at compile time (potentially).
 */
#define GOBIND_MODULE(t_name, t_param)                                     \
  void GOBIND_INTERNAL_FN(populate, t_name)(gobind::GolangModuleFactory&); \
  extern "C" {                                                             \
  GolangModule* GOBIND_INTERNAL_FN(init, t_name)()                         \
  {                                                                        \
    using gobind::GolangModuleFactory;                                     \
    using gobind::valid_module_name;                                       \
    GolangModuleFactory factory{};                                         \
    auto is_valid{valid_module_name(#t_name)};                             \
    if(!is_valid) {                                                        \
      assert(false && ERRORMSG_INVALID_GOLANG_MODULE_NAME);                \
    }                                                                      \
    factory.create_module(#t_name);                                        \
    GOBIND_INTERNAL_FN(populate, t_name)(factory);                         \
    factory.compile_module();                                       \
    return factory.get_module();                                           \
  }                                                                        \
  }                                                                        \
  auto GOBIND_INTERNAL_FN(populate, t_name)(gobind::GolangModuleFactory    \
                                            & t_param) -> void
// END GOBIND_MODULE.

#endif // GOBIND_HPP
