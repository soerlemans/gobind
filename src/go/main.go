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

// #include "gobind.h"

// RTLD_LAZY is a macro need to export by assigning it.
const int RTLD_LAZY_MODE = RTLD_LAZY;
*/
import "C"

// Regular Imports:
import (
	"errors"
	"fmt"
	"github.com/alexflint/go-arg"
	"log"
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
	VERSION = "0.1"
)

var args Arguments

// Functions:
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

func main() {
	// Parse and handle arguments.
	arg.MustParse(&args)

	fmt.Printf("I: %s, O: %s\n", args.InputFile, args.OutputFile)

	// Load the shared library
	handle, err := dlopen(args.InputFile)
	if err != nil {
		log.Fatal(err)
		return
	}
	defer dlclose(handle)

	_, err = dlsym(handle, "gobind_registered_modules")
	if err != nil {
		log.Fatal(err)
		return
	}
}
