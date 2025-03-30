package main

/*!
 * @file
 * This will contain the API for loading the bindings generated from.
 * The C++ side.
 */

/*
#cgo LDFLAGS: -ldl
#include <dlfcn.h>
#include <stdio.h>

void* load_library(const char* lib_path) {
    return dlopen(lib_path, RTLD_LAZY);
}

void* load_symbol(void* handle, const char* symbol_name) {
    return dlsym(handle, symbol_name);
}

void close_library(void* handle) {
    dlclose(handle);
}
*/
import "C"

// Regular Imports:
import (
	"fmt"
	"github.com/alexflint/go-arg"
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
func main() {
	// Parse and handle arguments.
	arg.MustParse(&args)

	fmt.Printf("I: %s, O: %s\n", args.InputFile, args.OutputFile)

	// Load the shared library
	handle := C.load_library(C.CString(args.InputFile))
	if handle == nil {
		fmt.Println("Error loading library:", C.dlerror())
		return
	}
}
