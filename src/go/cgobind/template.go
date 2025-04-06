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
	//	"unsafe"
	"os"
	"text/template"

	_ "github.com/soerlemans/gobind/cgobind/c_wrapper"
	"github.com/soerlemans/gobind/util"
)

// TODO: Figure this out.
// #cgo CFLAGS: -I {{OutputDir}}/include/

// Globals:
const (
	MODULE_TEMPLATE = `package {{.Package}}
/*
#cgo LDFLAGS: -ldl

// C wrapper includes:
#include "cgobind.h"
*/
import "C"

// Functions:
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

		functions[index] = FunctionData{functionName, "", "void"}
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
	// Create the C header file
	moduleFile, err := os.Create(t_modulePath)
	if err != nil {
		return TemplateContext{}, err
	}

	ctx := TemplateContext{t_module, moduleFile, nil}
	ctx.Tmpl, err = template.New(t_modulePath).Parse(MODULE_TEMPLATE)
	if err != nil {
		return ctx, err
	}

	return ctx, nil
}

// Functions:
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
