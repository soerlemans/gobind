/*
 * This will contain the API for loading the bindings generated from.
 * The C++ side.
 */
package main

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

void* call_func(void* t_func) {
    return ((void_fn_ptr)t_func)();
}
*/
import "C"

// Regular Imports:
import (
	"errors"
	"fmt"
	"github.com/alexflint/go-arg"
	"os"
	"unsafe"
	"github.com/soerlemans/gobind/util"
	// "text/template"
)

// Arguments Struct:
type Arguments struct {
	InputFile  string `arg:"-f,--file" help:"Path to file containing queries."`
	OutputFile string `arg:"-o,--output" help:"Write to output file instead of terminal." default:""`
}

// Arguments Methods:
func (Arguments) Version() string {
	return fmt.Sprintf("Version: %s", VERSION)
}

// Globals:
const (
	VERSION         = "0.1"
	DEBUG           = true
	GOBIND_INIT_FMT = "gobind_init_%s"
	EXIT_CODE_ERR   = 1
)

var args Arguments

// Functions:
func initArgs() error {
	// Parse and handle arguments.
	arg.MustParse(&args)

	// TODO: Create a function for this logging.
	// Logging:
	if len(args.InputFile) != 0 {
		util.Logf("Input: %s", args.InputFile)
	}

	if len(args.OutputFile) != 0 {
		util.Logf("Output: %s", args.OutputFile)
	}

	_, err := os.Stat(args.InputFile)
	if err != nil {
		return err
	}

	return nil
}

func dlopen(t_path string) (unsafe.Pointer, error) {
	handle := C.dlopen(C.CString(t_path), C.RTLD_LAZY_MODE)
	if handle == nil {
		err_msg := C.dlerror()
		err := errors.New(C.GoString(err_msg))

		return handle, err
	}

	return handle, nil
}

func dlsym(t_handle unsafe.Pointer, t_symbol_name string) (unsafe.Pointer, error) {
	// Load a symbol (function) from the library
	symbol := C.dlsym(t_handle, C.CString(t_symbol_name))
	util.Logf("dlsym(%s): %p", t_symbol_name, symbol)
	if symbol == nil {
		err_msg := C.dlerror()
		err := errors.New(C.GoString(err_msg))

		return symbol, err
	}

	return symbol, nil
}

func dlclose(t_handle unsafe.Pointer) {
	C.dlclose(t_handle)
}

func gobindRegisteredModules(t_handle unsafe.Pointer) ([]string, error) {
	var modules []string

	sym, err := dlsym(t_handle, "gobind_registered_modules")
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

func walkModules(t_registeredModules []string) {
	for _, name := range t_registeredModules {
		gobindInitFunctionName := fmt.Sprintf(GOBIND_INIT_FMT, name)
		util.Logf("Init function: %s", gobindInitFunctionName)
	}
}

func main() {
	err := initArgs()
	if err != nil {
		util.Fail(err)
	}

	// Load the shared library
	handle, err := dlopen(args.InputFile)
	if err != nil {
		util.Fail(err)
	}
	defer dlclose(handle)

	registeredModules, err := gobindRegisteredModules(handle)
	if err != nil {
		util.Fail(err)
	}

	walkModules(registeredModules)
}
