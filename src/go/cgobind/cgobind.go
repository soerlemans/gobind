/*
 Bindings for interacting with the generated C dynamic library.

*/
package cgobind

// TODO: For the cgo part we need to do some more thinking.

/*
#cgo LDFLAGS: -ldl
// C Includes:
#include <dlfcn.h>
#include <stdio.h>

#include "/home/hackerman/Projects/Git/Personal/gobind/src/cpp/gobind/gobind.h"

// RTLD_LAZY is a macro need to export by assigning it.
const int RTLD_LAZY_MODE = RTLD_LAZY;

//
typedef void* (*void_fn_ptr)();

//
typedef void* (*void_fn_ptr)();

void* call_func(void* t_func) {
    return ((void_fn_ptr)t_func)();
}
*/
import "C"

// Regular Imports:
import (
	"errors"
	"github.com/soerlemans/gobind/util"
	"unsafe"
)

// Functions:
func DlOpen(t_path string) (unsafe.Pointer, error) {
	handle := C.dlopen(C.CString(t_path), C.RTLD_LAZY_MODE)
	if handle == nil {
		err_msg := C.dlerror()
		err := errors.New(C.GoString(err_msg))

		return handle, err
	}

	return handle, nil
}

func DlSym(t_handle unsafe.Pointer, t_symbol_name string) (unsafe.Pointer, error) {
	// Load a symbol (function) from the library
	symbol := C.dlsym(t_handle, C.CString(t_symbol_name))
	util.Logf("DlSym(%s): %p", t_symbol_name, symbol)
	if symbol == nil {
		err_msg := C.dlerror()
		err := errors.New(C.GoString(err_msg))

		return symbol, err
	}

	return symbol, nil
}

func DlClose(t_handle unsafe.Pointer) {
	C.dlclose(t_handle)
}

// Return the names of registered modules.
func RegisteredModules(t_handle unsafe.Pointer) ([]string, error) {
	var modules []string

	sym, err := DlSym(t_handle, "gobind_registered_modules")
	if err != nil {
		return modules, err
	}

	voidPtr := C.call_func(sym)
	gobindModules := (*C.GobindModules)(unsafe.Pointer(voidPtr))

	size := int(gobindModules.m_size)
	util.Logf("Module count: %d", size)

	cStrs := unsafe.Slice(gobindModules.m_modules, size)

	modules = make([]string, size)
	for i, cStr := range cStrs {
		modules[i] = C.GoString(cStr)

		util.Logf("Modules[%d]: %s", i, modules[i])
	}

	return modules, err
}
