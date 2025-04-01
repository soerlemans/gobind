#include "gobind_module.h"

// STL Includes:
#include <cctype>
#include <string_view>

// Local Includes:
#include "gobind_module_factory.hpp"

// Functions:
Error gobind_module_create(GobindModule** t_module, const char* t_name)
{
  auto& module_ptr{*t_module};

  Error error{ERROR_FAIL, nullptr};
  module_ptr = new GobindModule{};

  const std::string_view name{t_name};
  if(!gobind::valid_module_name(name)) {
    error_fail(&error, ERRORMSG_INVALID_GOBIND_MODULE_NAME);

    goto cleanup;
  }

  return error;

cleanup:
  gobind_module_free(&module_ptr);

  return error;
}

void gobind_module_free(GobindModule** t_module)
{
  auto& module_ptr{*t_module};

  gobind_function_table_free(&module_ptr->m_fn_table);
  delete module_ptr;

  module_ptr = nullptr;
}
