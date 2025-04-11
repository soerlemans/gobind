/*
This will contain the API for loading the bindings generated from the C++ side.
*/
package main

import (
	"github.com/soerlemans/gobind/src/cmd/gobind/bind"

	util "github.com/soerlemans/gobind/src/lib/go_util"
)

func main() {
	err := initArgs()
	util.FailIf(err)

	// Bind the library modules.
	err = bind.Bind(args.InputFile, args.OutputDir)
	util.FailIf(err)
}
