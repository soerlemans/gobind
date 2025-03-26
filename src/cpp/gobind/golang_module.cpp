#include "golang_module.h"

// STL Includes:
#include <string_view>

namespace {
auto verify_module_path(const std::string_view t_module_name) -> bool
{
  bool valid{true};

  // Module names must be valid ASCII.
  for(const auto ch : t_module_name) {
    // TODO: Verify module name.
  }

  return valid;
}
} // namespace

// Functions:
GolangModule* golang_module_create(const char* t_module_name)
{
  GolangModule* module_ptr{nullptr};

  return module_ptr;
}

void golang_module_free(GolangModule* t_module)
{}
