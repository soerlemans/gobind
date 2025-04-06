/*
This will contain the API for loading the bindings generated from the C++ side.
*/
package cgobind

/*
#cgo CFLAGS: -I c_wrapper/ -I ../../cpp/
#cgo LDFLAGS: -ldl

// C Includes:
#include "cgobind_wrapper.h"
*/
import "C"

// Regular Imports:
import (
	//	"text/template"
	//	"unsafe"
	_ "github.com/soerlemans/gobind/cgobind/c_wrapper"
	"github.com/soerlemans/gobind/util"
)

// Globals:
const (
	PROLOGUE = `package {{.Package}}
/*
#cgo CFLAGS: -I {{OutputDir}}/include/
#cgo LDFLAGS: -ldl

// C wrapper includes:
#include "cgobind.h"
*/
import "C"
`

	FUNC_TEMPLATE = `func {{.Name}}() {{.ReturnType}} {}`
)

// Structs:
type PrologueData struct {
	Package   string ``
	OutputDir string ``
}

type FunctionData struct {
	Package   string ``
	OutputDir string ``
}

func prologue(t_module *C.GobindModule) {}
func epilogue(t_module *C.GobindModule) {}

func generate(t_module *C.GobindModule, t_modulePath string) error {
	util.Logf("Module path: %s", t_modulePath)

	return nil

}
