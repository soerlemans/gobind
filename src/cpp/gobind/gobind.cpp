#include "gobind.h"

// STL Includes:
#include <vector>

// Internal:
namespace {
// Aliases:
using ModuleNamesVec = std::vector<const char*>;

// Globals:
ModuleNamesVec name_vec{};
GobindRegistery registery{static_cast<const char**>(name_vec.data()), 0};
} // namespace

//  Functions:
const GobindRegistery* gobind_registery()
{
  registery.m_modules = name_vec.data();
  registery.m_size = name_vec.size();

  return &registery;
}

void gobind_register_module(const char* t_name)
{
  name_vec.push_back(t_name);
}

// Volatile Function Pointers:
const GobindRegistery* (*volatile gobind_volatile_registery_ptr)(void) =
  gobind_registery;
