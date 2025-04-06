/*
This will contain the API for loading the bindings generated from the C++ side.
*/
package main

// Regular Imports:
import (
	"github.com/soerlemans/gobind/cgobind"
	"github.com/soerlemans/gobind/util"
	"unsafe"
)

func walkModules(t_handle unsafe.Pointer, t_registeredModules []string) error {
	for _, name := range t_registeredModules {
		module, err := cgobind.InitModule(t_handle, name)
		if err != nil {
			return err
		}

		err = cgobind.CallFunction(t_handle, module, "hello_world")
		if err != nil {
			return err
		}

	}

	return nil
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
	err = walkModules(handle, registeredModules)
	util.FailIf(err)
}
