/*
Bindings for interacting with the generated C dynamic library.
*/
package bind

/*
#cgo CFLAGS: -I../../../lib
#cgo LDFLAGS: -ldl

// C Includes:
#include "cgobind/cgobind_helper.h"
*/
import "C"

import (
	"errors"
	"fmt"
	"os"
	"unsafe"

	util "github.com/soerlemans/gobind/src/lib/go_util"
	_ "github.com/soerlemans/gobind/src/lib/cgobind"
)

// Globals:
const (
	GOBIND_INIT_FMT = "gobind_init_%s"
)

// Constraints:
type CIntType interface {
	C.int8_t |
		C.int16_t |
		C.int32_t |
		C.int64_t |
		C.uint8_t |
		C.uint16_t |
		C.uint32_t |
		C.uint64_t
}

// Functions:
func DlOpen(t_path string) (unsafe.Pointer, error) {
	handle := C.dlopen_lazy(C.CString(t_path))
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

func CPtr2Array[ArrayType any, CInt CIntType](t_ptr *ArrayType, t_size CInt) []ArrayType {
	size := int(t_size)
	util.Logf("Array size: %d", size)
	array := unsafe.Slice(t_ptr, size)

	return array
}

// Return the names of registered modules.
func RegisteredModules(t_handle unsafe.Pointer) ([]string, error) {
	var modules []string

	sym, err := DlSym(t_handle, "gobind_registery")
	if err != nil {
		return modules, err
	}

	gobindModules := C.call_registered_modules(sym)

	size := int(gobindModules.m_size)
	util.Printf("Module count: %d", size)

	cStrs := unsafe.Slice(gobindModules.m_modules, size)

	modules = make([]string, size)
	for i, cStr := range cStrs {
		modules[i] = C.GoString(cStr)

		util.Printf("Modules[%d]: %s", i, modules[i])
	}

	return modules, err
}

func InitModule(t_handle unsafe.Pointer, t_name string) (*C.GobindModule, error) {
	var module *C.GobindModule

	initFunctionName := fmt.Sprintf(GOBIND_INIT_FMT, t_name)
	util.Logf("Init function: %s", initFunctionName)

	sym, err := DlSym(t_handle, initFunctionName)
	if err != nil {
		return module, err
	}

	modulePtr := C.call_gobind_module_init(sym)
	module = (*C.GobindModule)(modulePtr)

	util.Logf("Module name: %s", C.GoString(module.m_name))

	return module, err
}

/*
func freeModule(t_handle, unsafe.Pointer) error {
sym, err := DlSym(t_handle, "gobind_module_free")
if err != nil {
return err
}
}
*/

/*
func CallFunction(t_handle unsafe.Pointer, t_module *C.GobindModule, t_name string) error {
	fn_table := t_module.m_fn_table

	functions := CPtr2Array(fn_table.m_functions, fn_table.m_size)

	for index := 0; index < int(fn_table.m_size); index++ {
		function := functions[index]
		functionName := C.GoString(function.m_name)

		sym, err := DlSym(t_handle, "gtype2str")
		if err != nil {
			return err
		}

		C.call_gtype2str(sym, function.m_return_type.m_type)
		go_str := C.GoString(rt_str)

		util.Logf("Return type: %T", function.m_return_type.m_type)

		util.Logf("Calling function[%d]: %s", index, functionName)
		C.call_void_func(unsafe.Pointer(function.m_fn))
	}

	return nil
}
*/

func walkModules(t_handle unsafe.Pointer, t_registeredModules []string, t_libraryPath string, t_outputDir string) error {
	for _, name := range t_registeredModules {
		// Obtain the module.
		module, err := InitModule(t_handle, name)
		if err != nil {
			return err
		}

		// FIXME: Free the module.
		// defer freeModule(module)
		moduleDir := fmt.Sprintf("%s%s", t_outputDir, name)
		os.Mkdir(moduleDir, 0755)

		// Create the golang module path.
		modulePath := fmt.Sprintf("%s/%s.go", moduleDir, name)
		util.Logf("Module path: %s", modulePath)

		err = generate(module, t_libraryPath, modulePath)
		if err != nil {
			return err
		}
	}

	return nil
}

func Bind(t_libraryPath string, t_outputDir string) error {
	// Load the shared library handle.
	handle, err := DlOpen(t_libraryPath)
	if err != nil {
		util.Logf("Failed to open: %s", t_libraryPath)
		return err
	}

	defer DlClose(handle)

	// Get names of the modules that where registered.
	registeredModules, err := RegisteredModules(handle)
	if err != nil {
		return err
	}

	// Make sure that the output directory ends in a slash.
	size := len(t_outputDir)
	lastChar := t_outputDir[size-1]
	if lastChar != '/' {
		t_outputDir += "/"

	}

	// Create output directory.
	os.Mkdir(t_outputDir, 0755)

	// walkModules and create the modules.
	err = walkModules(handle, registeredModules, t_libraryPath, t_outputDir)
	if err != nil {
		return err
	}

	return nil
}
