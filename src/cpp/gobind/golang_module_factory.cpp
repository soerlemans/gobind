#include "golang_module_factory.hpp"

// Local Includes:
#include "gobind.h"

namespace gobind {
auto GolangModuleFactory::create_module(const char* t_name) -> Error
{
  const auto error{golang_module_create(&m_module, t_name)};
  if(error.m_code != ERROR_OK) {
    return error;
  }

  return error;
}

auto GolangModuleFactory::compile_module() -> void
{
  // Create function pointer table.
  const auto size{m_fn_list.size()};
  auto& fn_table{m_module->m_fn_table};

  golang_function_table_create(&fn_table, size);

  // FIXME: Figure out a safe way to use std::move() here.
  std::size_t index{0};
  for(auto& fn : m_fn_list) {
    fn_table->m_entries[index] = fn;

    index++;
  }
}

auto GolangModuleFactory::get_module() -> GolangModule*
{
  return m_module;
}
} // namespace gobind
