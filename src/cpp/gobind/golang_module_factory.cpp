#include "golang_module_factory.hpp"

namespace gobind {

auto GolangModuleFactory::create_module(const std::string_view t_name) -> Error
{}


auto GolangModuleFactory::get_module() -> GolangModule*
{
  return m_module;
}
} // namespace gobind
