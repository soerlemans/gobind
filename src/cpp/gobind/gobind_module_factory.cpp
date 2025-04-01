#include "gobind_module_factory.hpp"

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

  gobind_function_table_create(&fn_table, size);

  // FIXME: Figure out a safe way to use std::move() here.
  std::size_t index{0};
  for(auto& fn : m_fn_list) {
    fn_table->m_entries[index] = fn;

    index++;
  }
}

auto GobindModuleFactory::get_module() -> GobindModule*
{
  return m_module;
}
} // namespace gobind
