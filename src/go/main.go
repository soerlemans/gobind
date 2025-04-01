/*
This will contain the API for loading the bindings generated from the C++ side.
*/
package main

// Regular Imports:
import (
	"fmt"
	"github.com/soerlemans/gobind/cgobind"
	"github.com/soerlemans/gobind/util"
	// "text/template"
)

// Globals:
const (
	GOBIND_INIT_FMT = "gobind_init_%s"
)

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
	handle, err := cgobind.DlOpen(args.InputFile)
	if err != nil {
		util.Fail(err)
	}
	defer cgobind.DlClose(handle)

	registeredModules, err := cgobind.RegisteredModules(handle)
	if err != nil {
		util.Fail(err)
	}

	walkModules(registeredModules)
}
