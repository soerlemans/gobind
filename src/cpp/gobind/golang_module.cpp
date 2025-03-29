#include "golang_module.h"

// STL Includes:
#include <cctype>
#include <string_view>

// Local Includes:
#include "golang_module_factory.hpp"

// Functions:
Error golang_module_create(GolangModule** t_module, const char* t_name)
{
  auto& module_{*t_module};

  Error error{ERROR_FAIL, nullptr};
  module_ = new GolangModule{};

  const std::string_view name{t_name};
  if(!gobind::valid_module_name(name)) {
    error_fail(&error, ERRORMSG_INVALID_GOLANG_MODULE_NAME);

    goto cleanup;
  }

  return error;

cleanup:
  golang_module_free(&module_);

  return error;
}

void golang_module_free(GolangModule** t_module)
{
  auto& module_{*t_module};

  delete module_;

  module_ = nullptr;
}
