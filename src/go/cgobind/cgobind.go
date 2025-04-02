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
typedef void* (*void_fn_ptr)(void);

//
typedef GobindModule* (*gobind_fn_ptr)(void);

void* call_void_func(void* t_func) {
    return ((void_fn_ptr)t_func)();
}

GobindModule* call_gobind_module_init(void* t_func) {
    return ((gobind_fn_ptr)t_func)();
}

*/
import "C"

import (
	"errors"
	"fmt"
	"github.com/soerlemans/gobind/util"
	"unsafe"
)

// Globals:
const (
	GOBIND_INIT_FMT = "gobind_init_%s"
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

// func CPtr2Array[T any, S C.int | C.size_t](t_ptr *T, t_size S) []T {
// 	size := int(t_size)
// 	util.Logf("Size: %d", size)
// 	array := unsafe.Slice(t_ptr, size)

// 	return array
// }

// Return the names of registered modules.
func RegisteredModules(t_handle unsafe.Pointer) ([]string, error) {
	var modules []string

	sym, err := DlSym(t_handle, "gobind_registery")
	if err != nil {
		return modules, err
	}

	voidPtr := C.call_void_func(sym)
	gobindModules := (*C.GobindRegistery)(unsafe.Pointer(voidPtr))

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

func InitModule(t_handle unsafe.Pointer, t_name string) (C.GobindModule, error) {
	var module C.GobindModule

	initFunctionName := fmt.Sprintf(GOBIND_INIT_FMT, t_name)
	util.Logf("Init function: %s", initFunctionName)

	sym, err := DlSym(t_handle, initFunctionName)
	if err != nil {
		return module, err
	}

	module_ := C.call_gobind_module_init(sym)
	util.Logf("Module name: %s", C.GoString(module_.m_name))

	util.Logf("FnTable: %p", module.m_fn_table)
	// util.Logf("FnTable: %d", fn_table.m_size)
	// util.Logf("FnTable: %p", fn_table.m_entries)
	// _ = unsafe.Slice(fn_table.m_entries, int(fn_table.m_size))
	// fn_array := CPtr2Array(fn_table.m_entries, fn_table.m_size)
	//for _, fn := range fn_array {
	//	util.Logf("Function name: %s", C.GoString(fn.m_name))
	//}

	return module, err
}
