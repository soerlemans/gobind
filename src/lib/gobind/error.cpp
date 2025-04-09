#include "error.h"

// STL Includes:
#include <iostream>

// Functions:
void error_ok(Error* t_error)
{
  auto& [code, msg] = *t_error;
  code = ERROR_OK;
  msg = nullptr;
}

void error_fail(Error* t_error, const char* t_msg)
{
  auto& [code, msg] = *t_error;

  code = ERROR_FAIL;
  msg = t_msg;
}

void error_assert(const Error* t_error)
{
  const auto& [code, msg] = *t_error;

  if(code != ERROR_OK) {
    std::cerr << "Error (" << code << "): " << msg << '\n';
    std::exit(code);
  }
}
