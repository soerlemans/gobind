#include "gobind.h"

// STL Includes:
#include <vector>

// Internal:
namespace {
// Aliases:
using ModulesVec = std::vector<GolangModule>;

// Globals:
ModulesVec modules{};
GobindModules registered_modules{modules.data(), 0};
} // namespace

//  Functions:
const GobindModules* gobind_registered_modules()
{
  registered_modules.m_modules = modules.data();

  return &registered_modules;
}

void gobind_register_module(GolangModule* t_module)
{
  modules.push_back(*t_module);
}
