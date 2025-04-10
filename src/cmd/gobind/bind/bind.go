/*
Bindings for interacting with the generated C dynamic library.
*/
package bind

import (
	"fmt"
	"os"
	"unsafe"

	"github.com/soerlemans/gobind/src/lib/cgobind"
)

func walkModules(t_handle unsafe.Pointer, t_registeredModules []string, t_libraryPath string, t_outputDir string) error {
	for _, name := range t_registeredModules {
		// Obtain the module.
		module, err := cgobind.InitModule(t_handle, name)
		if err != nil {
			return err
		}

		// FIXME: Free the module.
		// defer freeModule(module)

		// Create the golang module path.
		modulePath := fmt.Sprintf("%s%s.go", t_outputDir, name)

		err = generate(module, t_libraryPath, modulePath)
		if err != nil {
			return err
		}
	}

	return nil
}

func Bind(t_libraryPath string, t_outputDir string) error {
	// Load the shared library handle.
	handle, err := cgobind.DlOpen(t_libraryPath)
	if err != nil {
		return err
	}

	defer cgobind.DlClose(handle)

	// Get names of the modules that where registered.
	registeredModules, err := cgobind.RegisteredModules(handle)
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
