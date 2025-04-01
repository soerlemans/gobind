package main

/*!
 * @file
 * This will contain the API for loading the bindings generated from.
 * The C++ side.
 */

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
	"log"
	"os"
	"unsafe"
	// "os"
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
func fail(err error) {
	log.Fatalln(err)
	os.Exit(EXIT_CODE_ERR)
}

func logf(format string, args ...interface{}) {
	if DEBUG {
		log.Printf(format, args...)
	}
}

func initArgs() error {
	// Parse and handle arguments.
	arg.MustParse(&args)

	// TODO: Create a function for this logging.
	// Logging:
	if len(args.InputFile) != 0 {
		logf("Input: %s\n", args.InputFile)
	}

	if len(args.OutputFile) != 0 {
		logf("Output: %s\n", args.OutputFile)
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
	logf("dlsym(%s): %p", t_symbol_name, symbol)
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
	logf("Module count: %d\n", size)

	ptrs := unsafe.Slice(gobindModules.m_modules, size)

	modules = make([]string, size)
	for i, ptr := range ptrs {
		modules[i] = C.GoString(ptr)

		logf("Modules[%d]: %s\n", i, modules[i])
	}

	return modules, err
}

func walkModules(t_registered_names []string) {

}

func main() {
	err := initArgs()
	if err != nil {
		fail(err)
	}

	// Load the shared library
	handle, err := dlopen(args.InputFile)
	if err != nil {
		fail(err)
	}
	defer dlclose(handle)

	_, err = gobindRegisteredModules(handle)
	if err != nil {
		fail(err)
	}
}
