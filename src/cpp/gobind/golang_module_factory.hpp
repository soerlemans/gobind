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
#include <string_view>

// Local Includes:
#include "gobind.h"

namespace gobind {
// Classes:
class GolangModuleFactory {
  private:
  GolangModule* m_module;

  public:
  GolangModuleFactory() = default;

  auto create_module(std::string_view t_name) -> Error;

  // TODO: Overload the hell out of def.
  // auto def(std::string_view t_name) -> Error;

  auto get_module() -> GolangModule*;

  virtual ~GolangModuleFactory() = default;
};

// Functions:
// TODO: Maybe place this function in another header so.
// So that we can verify the module name at compile time.
constexpr auto valid_module_name(const std::string_view t_module_name) -> bool
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
