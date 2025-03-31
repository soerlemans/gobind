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
	VERSION       = "0.1"
	DEBUG         = true
	EXIT_CODE_ERR = 1
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

	//fn_ptr := (C.void_fn_ptr)(unsafe.Pointer(sym))
	//modules = fn_ptr()

	voidPtr := C.call_func(sym)
	gobindModules := (*C.GobindModules)(unsafe.Pointer(voidPtr))

	moduleCount := int(gobindModules.m_size)
	modulePtrs := (*[1 << 30]*C.char)(unsafe.Pointer(&gobindModules))[:moduleCount:moduleCount]

	logf("Module count: %d\n", moduleCount)

	modules = make([]string, moduleCount)
	for i, ptr := range modulePtrs {
		modules[i] = C.GoString(ptr)

		logf("Modules[%d]: %s\n", i, modules[i])
	}

	// modules[0] = gobindModules.m_modules[0]
	// logf("Modules[%d]: %s\n", 0, modules[0])

	return modules, err
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

	gobindRegisteredModules(handle)
	if err != nil {
		fail(err)
	}
}
