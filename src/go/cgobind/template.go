/*
This will contain the API for loading the bindings generated from the C++ side.
*/
package cgobind

/*
#cgo CFLAGS: -I include/ -I ../../cpp/
#cgo LDFLAGS: -ldl

// C Includes:
#include "cgobind.h"
#include "cgobind_wrapper.h"
*/
import "C"

// Regular Imports:
import (
	"github.com/soerlemans/gobind/util"
	"text/template"
	"unsafe"
)

// Globals:
const (
	PROLOGUE = `package {{.Package}}
/*
#cgo CFLAGS: -I {{OutputDir}}/include/
#cgo LDFLAGS: -ldl

#include "gobind.h"
*/
import "C"
`

	FUNC_TEMPLATE = `func {{.Name}}() {{.ReturnType}} {}`
)

// Structs:
type PrologueData struct{
	Package string ``
	OutputDir string ``
}

func generateModule(t_module *C.GobindModule) {}
