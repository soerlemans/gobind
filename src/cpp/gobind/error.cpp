#include "error.h"

// Functions:
void error_fail(Error* t_error, const char* t_msg)
{
  auto& [code, msg] = *t_error;

  code = ERROR_FAIL;
  msg = t_msg;
}

void error_check(Error* t_error)
{
  const auto& [code, msg] = *t_error;

  if(code != ERROR_OK) {
    // TODO: Assert/quit without memory leaks.
  }
}
