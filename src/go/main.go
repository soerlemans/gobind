/*
This will contain the API for loading the bindings generated from the C++ side.
*/
package main

// Regular Imports:
import (
	"github.com/soerlemans/gobind/cgobind"
	"github.com/soerlemans/gobind/util"
	"unsafe"
	// "text/template"
)

func walkModules(t_handle unsafe.Pointer, t_registeredModules []string) {
	for _, name := range t_registeredModules {
		cgobind.InitModule(t_handle, name)
	}
}

func main() {
	err := initArgs()
	util.FailIf(err)

	// Load the shared library handle.
	handle, err := cgobind.DlOpen(args.InputFile)
	util.FailIf(err)

	defer cgobind.DlClose(handle)

	// Get names of the modules that where registered.
	registeredModules, err := cgobind.RegisteredModules(handle)
	util.FailIf(err)

	// Walk the modules and create the source.
	walkModules(handle, registeredModules)
	util.FailIf(err)
}
