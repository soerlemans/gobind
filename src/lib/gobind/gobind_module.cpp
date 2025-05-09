#include "gobind_module.h"

// STL Includes:
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string_view>

// C Includes:
#include "gobind_function_table.h"

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

    gobind_module_free(&ptr);
  } else {
    // Set name after validation.
    ptr->m_name = t_name;

    // Allocate space for the function table.
    auto& fn_table{ptr->m_fn_table};
    gobind_function_table_create(&fn_table);
  }

  return error;
}

// TODO: One day clean this code up, maybe use an actual logging library.
void gobind_module_pprint(const GobindModule* t_module)
{
  if(!t_module) {
    std::cerr << "GobindModule nil!";
    return;
  }

  const auto& [name, fn_table] = *t_module;

  std::cout << "# GobindModule: " << name << '\n';
  gobind_function_table_pprint((const GobindFunctionTable*)&fn_table);
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
