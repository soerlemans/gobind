#ifndef GOBIND_HPP
#define GOBIND_HPP

/*!
 * @file
 *
 * C++ API for registering the C++ functions for cgo to import later.
 */

// STL Includes:
#include <iostream>
#include <string_view>

// Local Includes:
#include "gobind.h"
#include "macros.h"

// Macros:
//
#define GOBIND_INTERNAL_FN(t_name, t_module_name) \
  GOBIND_CONCAT(gobind_##t_name##_, t_module_name)

/*!
 * Define a Golang module that can be included from Golang.
 * This macro constructs two
 */
#define GOBIND_MODULE(t_name, t_param)                               \
  extern "C" {                                                       \
  void GOBIND_INTERNAL_FN(populate, t_name)(GolangModule * t_param); \
  GolangModule* GOBIND_INTERNAL_FN(init, t_name)()                   \
  {                                                                  \
    GolangModule* module_ptr{nullptr};                               \
    auto error{golang_module_create(module_ptr, #t_name)};           \
    auto& [code, msg] = error;                                       \
    if(code != ERROR_OK) {                                           \
    }                                                                \
    GOBIND_INTERNAL_FN(populate, t_name)(module_ptr);                \
    return module_ptr;                                               \
  }                                                                  \
  }                                                                  \
  extern "C" void GOBIND_INTERNAL_FN(populate, t_name)(GolangModule * t_param)

namespace gobind {
// Functions:
auto register_function(std::string_view t_id) -> void;
} // namespace gobind

#endif // GOBIND_HPP
