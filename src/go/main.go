/*
This will contain the API for loading the bindings generated from the C++ side.
*/
package main

import (
	"github.com/soerlemans/gobind/cgobind"
	"github.com/soerlemans/gobind/util"
)

func main() {
	err := initArgs()
	util.FailIf(err)

	// Bind the library modules.
	err = cgobind.Bind(args.InputFile, args.OutputDir)
	util.FailIf(err)
}
