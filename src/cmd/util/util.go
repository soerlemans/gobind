/*
Utility functions for gobind.
*/
package util

// Regular Imports:
import (
	"fmt"
	"log"
	"os"
)

// Globals:
const (
	DEBUG         = true
	EXIT_CODE_ERR = 1
)

// Functions:
func Fail(t_err error) {
	log.Fatalln(t_err)

	os.Exit(EXIT_CODE_ERR)
}

func FailIf(t_err error) {
	if t_err != nil {
		Fail(t_err)
	}
}

func Logf(t_fmt string, t_args ...interface{}) {
	if DEBUG {
		fmtLn := fmt.Sprintln(t_fmt)
		log.Printf(fmtLn, t_args...)
	}
}

func Printf(t_fmt string, t_args ...interface{}) {
	fmtLn := fmt.Sprintln(t_fmt)

	if !DEBUG {
		// On non debug builds just print regularly.
		fmt.Printf(fmtLn, t_args...)
	} else {
		// Use log instead.
		log.Printf(fmtLn, t_args...)
	}
}
