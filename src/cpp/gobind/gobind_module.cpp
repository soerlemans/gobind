#include "gobind_module.h"

// STL Includes:
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string_view>

// Local Includes:
#include "alloc.hpp"
#include "gobind_module_factory.hpp"

// Functions:
Error gobind_module_create(GobindModule** t_module, const char* t_name)
{
  Error error{};
  error_ok(&error);

  auto& ptr{*t_module};
  ptr = gobind::malloc<GobindModule>();

  // Check the module name, if it is valid.
  const auto name_err{gobind::valid_module_name(t_name)};
  if(name_err.m_code != ERROR_OK) {
    error_fail(&error, ERRORMSG_INVALID_GOBIND_MODULE_NAME);

    goto cleanup;
  }

  ptr->m_name = t_name;

  return error;

cleanup:
  gobind_module_free(&ptr);

  return error;
}

void gobind_module_free(GobindModule** t_module)
{
  // FIXME: Check if t_module is nullptr (nullptr dereference).
  // FIXME: Then check if module_ptr is nullptr (prevent double free).
  auto& module_ptr{*t_module};

  gobind_function_table_free(&module_ptr->m_fn_table);
  std::free(module_ptr);

  module_ptr = nullptr;
}
