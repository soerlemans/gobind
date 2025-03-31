#include "gobind.h"

// STL Includes:
#include <vector>

// Internal:
namespace {
// Aliases:
using ModulesVec = std::vector<const char*>;

// Globals:
ModulesVec modules{};
GobindModules registered_modules{static_cast<const char**>(modules.data()), 0};
} // namespace

//  Functions:
const GobindModules* gobind_registered_modules()
{
  registered_modules.m_modules = modules.data();

  return &registered_modules;
}

void gobind_register_module(const char* t_name)
{
  modules.push_back(t_name);
}

// Volatile Function Pointers:
const GobindModules* (*volatile gobind_modules)(void) =
  gobind_registered_modules;
