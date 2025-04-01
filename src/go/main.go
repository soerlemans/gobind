/*
 * This will contain the API for loading the bindings generated from.
 * The C++ side.
 */
package main

// Regular Imports:
import (
	"fmt"
	"github.com/alexflint/go-arg"
	"github.com/soerlemans/gobind/cgobind"
	"github.com/soerlemans/gobind/util"
	"os"
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
func initArgs() error {
	// Parse and handle arguments.
	arg.MustParse(&args)

	// TODO: Create a function for this logging.
	// Logging:
	if len(args.InputFile) != 0 {
		util.Logf("Input: %s", args.InputFile)
	}

	if len(args.OutputFile) != 0 {
		util.Logf("Output: %s", args.OutputFile)
	}

	_, err := os.Stat(args.InputFile)
	if err != nil {
		return err
	}

	return nil
}

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
