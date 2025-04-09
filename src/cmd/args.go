package main

// Regular Imports:
import (
	"fmt"
	"github.com/alexflint/go-arg"
	"github.com/soerlemans/gobind/cmd/util"
	"os"
)

// Arguments Struct:
type Arguments struct {
	InputFile string `arg:"-i,--input-file" help:"Path to file containing queries."`
	OutputDir string `arg:"-o,--output" help:"Write to output directory instead of current directory." default:"gbmod/"`
}

// Arguments Methods:
func (Arguments) Version() string {
	return fmt.Sprintf("Version: %s", VERSION)
}

// Globals:
const (
	VERSION = "0.1"
)

// Cli arguments variable.
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

	if len(args.OutputDir) != 0 {
		util.Logf("Output: %s", args.OutputDir)
	}

	_, err := os.Stat(args.InputFile)
	if err != nil {
		return err
	}

	return nil
}
