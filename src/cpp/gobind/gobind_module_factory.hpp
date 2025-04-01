#ifndef GOLANG_MODULE_FACTORY_HPP
#define GOLANG_MODULE_FACTORY_HPP

/*!
 * @file
 *
 * Helper class intended to construct the @ref GolangModule class.
 * This only helps with constructing the class.
 * The underlying @ref GolangModule is eventually passed to cgo.
 */

// STL Includes:
#include <cctype>
#include <functional>
#include <string_view>

// Local Includes:
#include "gobind.h"

namespace gobind {
// Aliases:
using FunctionList = std::vector<GolangFunction>;

// Classes:
class GolangModuleFactory {
  private:
  GolangModule* m_module;

  //! Calculate how many functions are needed.
  FunctionList m_fn_list;

  public:
  GolangModuleFactory() = default;

  // Methods:
  auto create_module(const char* t_name) -> Error;

  template<typename R, typename... Args>
  auto def(const char* t_name, R (*t_fn)(Args...)) -> Error;

  //! Create the @ref GolangModule with all the size calculations in place.
  auto compile_module() -> void;
  auto get_module() -> GolangModule*;

  virtual ~GolangModuleFactory() = default;
};

// GolangModuleFactory Template Methods:
template<typename Ret, typename... Args>
auto GolangModuleFactory::def(const char* t_name, Ret (*t_fn)(Args...)) -> Error
{
  // using CFnPtr = Ret (*)(Args...);

  GolangFunction fn{};
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
    if(!is_alpha_lower || !is_underscore) {
      valid = false;
      break;
    }
  }

  return valid;
}

} // namespace gobind

#endif // GOLANG_MODULE_FACTORY_HPP
