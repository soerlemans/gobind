#ifndef GOLANG_MODULE_FACTORY_HPP
#define GOLANG_MODULE_FACTORY_HPP

/*!
 * @file
 *
 * Helper class intended to construct the @ref GobindModule class.
 * This only helps with constructing the class.
 * The underlying @ref GobindModule is eventually extracted.
 * From the shared library by the Golang gobind binary.
 */

// STL Includes:
#include <cctype>
#include <iostream>
#include <string_view>
#include <vector>

// Local Includes:
#include "gobind.h"

namespace gobind {
// Aliases:
using FunctionList = std::vector<GobindFunction>;

// Classes:
class GobindModuleFactory {
  private:
  GobindModule* m_module;

  //! Calculate how many functions are needed.
  FunctionList m_fn_list;

  public:
  GobindModuleFactory() = default;

  // Methods:
  auto create_module(const char* t_name) -> Error;

  template<typename R, typename... Args>
  auto def(const char* t_name, R (*t_fn)(Args...)) -> Error;

  //! Create the @ref GobindModule with all the size calculations in place.
  auto compile_module() -> void;
  auto get_module() -> GobindModule*;

  virtual ~GobindModuleFactory() = default;
};

// GobindModuleFactory Template Methods:
template<typename Ret, typename... Args>
auto GobindModuleFactory::def(const char* t_name, Ret (*t_fn)(Args...)) -> Error
{
  // using CFnPtr = Ret (*)(Args...);

  GobindFunction fn{};
  fn.m_name = t_name;
  fn.m_fn = (VoidFnPtr)t_fn;

  m_fn_list.push_back(std::move(fn));

  // m_fn_list.emplace_back(t_name, (VoidFnPtr)t_fn);

  return {};
}

// Functions:
//! Used to verify the module name potentially at compile time.
constexpr inline auto valid_module_name(const std::string_view t_module_name)
  -> bool
{
  bool valid{true};

  constexpr auto underscore{'_'};

  // Module names must be valid ASCII.
  for(const auto ch : t_module_name) {
    const auto is_alpha_lower{std::isalpha(ch) && std::islower(ch)};
    const auto is_underscore{ch == underscore};

    // Only lowercase alpha numerics or underscores are allowed.
    const auto is_valid{is_alpha_lower || is_underscore};

    if(!is_valid) {
      valid = false;
      break;
    }
  }

  return valid;
}

} // namespace gobind

#endif // GObind_MODULE_FACTORY_HPP
