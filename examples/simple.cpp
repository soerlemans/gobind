// STL Includes:
#include <iostream>

// Library Includes:
#include <gobind/gobind.h>
#include <gobind/gobind.hpp>

auto add(const int t_l, const int t_r) -> int
{
  return t_l + t_r;
}

auto main() -> int
{
  const auto* registered{gobind_registered_modules()};

  for(auto index{0}; index < registered->m_size; index++) {
    const auto& modules{registered->m_modules};
    std::cout << "Name " << index << ": " << modules[index] << '\n';
  }
}

// Define  the simple module for the add function.
GOBIND_MODULE(simple, m)
{
  m.def("add", &add);
}
