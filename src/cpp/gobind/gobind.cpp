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

// Volatile Function Pointers:
const GobindModules* (*volatile gobind_modules)(void) =
  gobind_registered_modules;

//  Functions:
const GobindModules* gobind_registered_modules(void)
{
  registered_modules.m_modules = modules.data();

  return &registered_modules;
}

void gobind_register_module(GolangModule* t_module)
{
  modules.push_back(*t_module);
}
