// STL Includes:
#include <iostream>

// Library Includes:
#include <gobind/gobind.hpp>

/*!
 * @file
 * Windows: uses various calling conventions.
 * Unix: Uses cdecl.
 *
 * So in order to support Windows we need to check which calling conventions.
 * Golang supports besides cdecl.
 */

// Macros:
#ifdef _WIN32
// Windows:
#define CC_CDECL    __cdecl
#define CC_STDCALL  __stdcall
#define CC_FASTCALL __fastcall
#define CC_THISCALL __thiscall // Not supported yet.
// #define CC_VECTORCALL __vectorcall // Not supported yet.

constexpr bool g_is_windows{true};

#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
// Unix like systems:
// Unix like systems always use cdecl, only windows is a pain.
#define CC_CDECL
#define CC_STDCALL
#define CC_FASTCALL
#define CC_THISCALL

// #define CC_NAKED __attribute__((naked))

constexpr bool g_is_windows{false};
#endif

// Globals:
constexpr int g_success{1};
constexpr int g_fail{0};

// Functions:
CC_CDECL auto cc_cdecl() -> int
{
  if(g_is_windows) {
    std::cout << "Golang supports cdecl calling convention\n";

    return g_success;
  }

  return g_fail;
}

CC_STDCALL auto cc_stdcall() -> int
{
  if(g_is_windows) {
    std::cout << "Golang supports stdcall calling convention\n";

    return g_success;
  }

  return g_fail;
}

CC_FASTCALL auto cc_fastcall() -> int
{
  if(g_is_windows) {
    std::cout << "Golang supports fastcall calling convention\n";

    return g_success;
  }

  return g_fail;
}

// Test the calling convention
GOBIND_MODULE(calling_convention, m)
{
  m.def("cc_decl", &cc_cdecl);
  m.def("cc_stdcall", &cc_stdcall);
  m.def("cc_fastcall", &cc_fastcall);
}
