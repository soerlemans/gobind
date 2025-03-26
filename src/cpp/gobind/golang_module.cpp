#include "golang_module.h"

// STL Includes:
#include <cctype>
#include <string_view>

namespace {
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
} // namespace

// Functions:
Error golang_module_create(GolangModule* t_module, const char* t_name)
{
  Error error{ERROR_FAIL, nullptr};
  t_module = new GolangModule{};

  const std::string_view name{t_name};
  if(!valid_module_name(name)) {
    error_fail(&error, ERRORMSG_INVALID_GOLANG_MODULE_NAME);

    goto cleanup;
  }

  return error;

cleanup:
  golang_module_free(t_module);

  return error;
}

void golang_module_free(GolangModule* t_module)
{
  delete t_module;

  t_module = nullptr;
}
