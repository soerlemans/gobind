/*
This will contain the API for loading the bindings generated from the C++ side.
*/
package cgobind

/*
#cgo CFLAGS: -I c_wrapper/ -I ../../../lib/
#cgo LDFLAGS: -ldl

// C Includes:
#include "cgobind_wrapper.h"
*/
import "C"

// Regular Imports:
import (
	//	"unsafe"
	"os"
	"text/template"

	//_ "github.com/soerlemans/gobind/src/cmd/gobind/cgobind/c_wrapper"

	"github.com/soerlemans/gobind/src/cmd/gobind/util"
	_ "github.com/soerlemans/gobind/src/lib/cgobind"
)

// TODO: Figure this out.
// #cgo CFLAGS: -I {{OutputDir}}/include/

// Globals:
const (
	MODULE_TEMPLATE = `package {{.Package}}
/*
#cgo CFLAGS: -I/usr/local/include
#cgo LDFLAGS: -L/usr/local/lib -lgobind -ldl

// C wrapper includes:
#include "cgobind.h"
*/
import "C"

import (
        _ "github.com/soerlemans/gobind/src/cmd/gobind/cgobind/c_wrapper"
)

// Globals:
make(map[string]C.GobindFunction)

// Functions:
func init() {
    // fmt.Printf("Initializing %s...", "{{.Package}}")
    // TODO: Load dynamic library module into globals.
}
{{range .Functions}}
func {{.Name}}({{.Params}}) {{.ReturnType}} {
    return nil
}
{{end}}
`
)

// Structs:
type FunctionData struct {
	Name       string
	Params     string
	ReturnType string
}

type TemplateData struct {
	Package   string
	Functions []FunctionData
}

// Struct TemplateContext:
type TemplateContext struct {
	Module *C.GobindModule    ``
	File   *os.File           ``
	Tmpl   *template.Template ``
}

// Methods TemplateContext:
func (this *TemplateContext) ExtractFunctionData() []FunctionData {
	var functions []FunctionData

	functionTable := this.Module.m_fn_table
	functionTableSize := int(functionTable.m_size)

	functions = make([]FunctionData, functionTableSize)

	functionArray := CPtr2Array(functionTable.m_functions, functionTable.m_size)
	for index := 0; index < functionTableSize; index++ {
		function := functionArray[index]
		functionName := C.GoString(function.m_name)

		functions[index] = FunctionData{functionName, "", ""}
	}

	return functions
}

func (this *TemplateContext) ExtractTemplateData() TemplateData {
	moduleName := C.GoString(this.Module.m_name)
	functionData := this.ExtractFunctionData()

	return TemplateData{moduleName, functionData}
}

func (this *TemplateContext) Write() error {
	data := this.ExtractTemplateData()

	return this.Tmpl.Execute(this.File, data)
}

func (this *TemplateContext) Close() {
	this.File.Close()
}

// Factory functions TemplateContext:
func newTemplateContext(t_module *C.GobindModule, t_modulePath string) (TemplateContext, error) {
	// Create the golang module file.
	moduleFile, err := os.Create(t_modulePath)
	if err != nil {
		return TemplateContext{}, err
	}

	// Create the template context.
	ctx := TemplateContext{t_module, moduleFile, nil}
	ctx.Tmpl, err = template.New(t_modulePath).Parse(MODULE_TEMPLATE)
	if err != nil {
		return ctx, err
	}

	return ctx, nil
}

// Functions:
// TODO: We also need the library path in order to understand where to depend on.
// After we have generated the library.
func generate(t_module *C.GobindModule, t_modulePath string) error {
	util.Logf("Module path: %s", t_modulePath)

	ctx, err := newTemplateContext(t_module, t_modulePath)
	if err != nil {
		return err
	}
	defer ctx.Close()

	return ctx.Write()

	// return nil
}
