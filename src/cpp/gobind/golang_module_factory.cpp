#include "golang_module_factory.hpp"

// Local Includes:
#include "gobind.h"

namespace gobind {
auto GolangModuleFactory::create_module(const char* t_name) -> Error
{
  return golang_module_create(m_module, t_name);
}

auto GolangModuleFactory::compile_module() -> void
{}

auto GolangModuleFactory::get_module() -> GolangModule*
{
  return m_module;
}
} // namespace gobind
