#include "gobind_module.h"

// STL Includes:
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string_view>

// Local Includes:
#include "gobind_module_factory.hpp"

// Functions:
Error gobind_module_create(GobindModule** t_module, const char* t_name)
{
  auto& module_ptr{*t_module};

  Error error{ERROR_FAIL, nullptr};
  module_ptr = new GobindModule{};

  if(!gobind::valid_module_name(t_name)) {
    error_fail(&error, ERRORMSG_INVALID_GOBIND_MODULE_NAME);

    goto cleanup;
  }

  module_ptr->m_name = t_name;

  return error;

cleanup:
  gobind_module_free(&module_ptr);

  return error;
}

void gobind_module_invalid_name(const char* t_name)
{
  // clang-format off
  std::cerr << "Error: "
	    << std::quoted(t_name)
	    << ' '
            << ERRORMSG_INVALID_GOBIND_MODULE_NAME
	    << '\n';
  // clang-format on

  std::exit(ERROR_FAIL);
}

void gobind_module_free(GobindModule** t_module)
{
  auto& module_ptr{*t_module};

  gobind_function_table_free(&module_ptr->m_fn_table);
  delete module_ptr;

  module_ptr = nullptr;
}
