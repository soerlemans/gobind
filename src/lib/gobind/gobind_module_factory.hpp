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
#include "alloc.hpp"
#include "gobind.h"
#include "gobind_type_identify.hpp"

namespace gobind {
// Aliases:
using FunctionVec = std::vector<GobindFunction>;

// Classes:
class GobindModuleFactory {
  private:
  GobindModule* m_module;

  //! Calculate how many functions are needed.
  FunctionVec m_fn_list;

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
  const auto ret{sym_identify<Ret>()};
  const auto params{args_identify<Args...>()};

  const auto size{params.size()};

  GobindFunction fn{};
  fn.m_name = t_name;
  fn.m_fn = (VoidFnPtr)t_fn;
  fn.m_return_type = ret;

  // TODO: make params setting more elegant.
  if(size > 0) {
    fn.m_params = gobind::malloc<GobindType>(size);
  } else {
    fn.m_params = nullptr;
  }

  fn.m_params_size = size;

  auto index{0};
  for(auto&& sym : params) {
    //FIXME: lazy logging.
    // clang-format off
    std::cout << "Name: " << t_name
	      << " Param: " << ((sym.m_constant) ? "const " : "" )
	      << gtype2str(sym.m_type)
	      << ' ' << ((sym.m_pointer > 0) ? "*" : "")
	      << '\n';
    // clang-format on

    fn.m_params[index] = sym;
    index++;
  }

  m_fn_list.push_back(std::move(fn));

  return {};
}

// Functions:
//! Used to verify the module name potentially at compile time.
constexpr inline auto valid_module_name(const std::string_view t_module_name)
  -> Error
{
  Error error{};

  constexpr auto underscore{'_'};

  // Module names must be valid ASCII.
  for(const auto ch : t_module_name) {
    const auto is_alpha_lower{std::isalpha(ch) && std::islower(ch)};
    const auto is_underscore{ch == underscore};

    // Only lowercase alpha numerics or underscores are allowed.
    const auto is_valid{is_alpha_lower || is_underscore};

    if(!is_valid) {
      error_fail(&error, ERRORMSG_INVALID_GOBIND_MODULE_NAME);
      break;
    }
  }

  return error;
}
} // namespace gobind

#endif // GObind_MODULE_FACTORY_HPP
