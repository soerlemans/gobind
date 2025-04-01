#include "gobind.h"

// STL Includes:
#include <vector>

// Internal:
namespace {
// Aliases:
using ModulesVec = std::vector<const char*>;

// Globals:
ModulesVec modules_vec{};
GobindModules registered_modules{static_cast<const char**>(modules_vec.data()),
                                 0};
} // namespace

//  Functions:
const GobindModules* gobind_registered_modules()
{
  registered_modules.m_modules = modules_vec.data();
  registered_modules.m_size = modules_vec.size();

  return &registered_modules;
}

void gobind_register_module(const char* t_name)
{
  modules_vec.push_back(t_name);
}

// Volatile Function Pointers:
const GobindModules* (*volatile gobind_modules)(void) =
  gobind_registered_modules;
