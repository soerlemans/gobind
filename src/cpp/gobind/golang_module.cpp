#include "golang_module.h"

// STL Includes:
#include <cctype>
#include <string_view>

// Local Includes:
#include "golang_module_factory.hpp"

// Functions:
Error golang_module_create(GolangModule* t_module, const char* t_name)
{
  Error error{ERROR_FAIL, nullptr};
  t_module = new GolangModule{};

  const std::string_view name{t_name};
  if(!gobind::valid_module_name(name)) {
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
