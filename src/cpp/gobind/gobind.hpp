#ifndef GOBIND_HPP
#define GOBIND_HPP

/*!
 * @file
 *
 * C++ API for registering the C++ functions for cgo to import later.
 */

// STL Includes:
#include <string_view>

// Local Includes:
#include "golang_module.hpp"

// Macros:
//! Defins a Golang module that
#define GOBIND_MODULE(t_module_name, t_id) \
  auto define_gobind_module() -> GolangModule*

namespace gobind {
// Functions:
auto register_function(std::string_view t_id) -> void;
} // namespace gobind

#endif // GOBIND_HPP
