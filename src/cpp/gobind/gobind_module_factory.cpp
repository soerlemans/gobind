#include "gobind_module_factory.hpp"

// STL Includes:
#include <iostream>

// Local Includes:
#include "gobind.h"

namespace gobind {
auto GobindModuleFactory::create_module(const char* t_name) -> Error
{
  const auto error{gobind_module_create(&m_module, t_name)};
  if(error.m_code != ERROR_OK) {
    return error;
  }

  return error;
}

auto GobindModuleFactory::compile_module() -> void
{
  // Create function pointer table.
  const auto size{m_fn_list.size()};
  auto& fn_table{m_module->m_fn_table};

  // Resize too the size we need as we already know the size.
  gobind_function_table_resize(fn_table, size);

  // TODO: We could be more efficient by doing a raw copy.
  // But this is riskier/less safe.
  for(auto& fn : m_fn_list) {
    gobind_function_table_add(fn_table, &fn);
  }
}

auto GobindModuleFactory::get_module() -> GobindModule*
{
  return m_module;
}
} // namespace gobind
