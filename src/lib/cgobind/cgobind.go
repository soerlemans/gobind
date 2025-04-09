/*
Package is intended as a wrapper for building the C code.
For interfacing with the gobind C library from Golang.
*/
package cgobind

/*
#cgo CFLAGS: -I ..
#cgo LDFLAGS: -ldl

// C Includes:
#include "cgobind_wrapper.h"
*/
import "C"
