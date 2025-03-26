#ifndef ERROR_H
#define ERROR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// Enums:
//!
enum {
  ERROR_OK = 0,
  ERROR_FAIL = 1
};

// Structs:
//! Struct for dealing with error messages.
typedef struct {
  int m_code;
  const char* m_msg;
} Error;

// Functions:
  void error_fail(Error* t_error, const char* t_msg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // ERROR_H
