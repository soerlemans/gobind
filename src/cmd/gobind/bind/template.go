/*
This will contain the API for loading the bindings generated from the C++ side.
*/
package bind

/*
#cgo CFLAGS: -I ../../../lib/
#cgo LDFLAGS: -ldl

// C Includes:
#include "cgobind/cgobind_helper.h"
*/
import "C"

// Regular Imports:
import (
	//"unsafe"
	"os"
	"text/template"

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
#cgo LDFLAGS: -L/usr/local/lib -ldl -lcgobind -lgobind

// C wrapper includes:
#include "cgobind/cgobind.h"
*/
import "C"

import (
        "log"

	"github.com/soerlemans/gobind/src/lib/cgobind"
)

// Globals:
var exportedFunctions = make(map[string]C.GobindFunction)

// Functions:
func init() {
    handle, err := cgobind.DlOpen("{{.LibraryPath}}")
    if err != nil {
	log.Fatalln(err)
        return
    }

    // Get names of the modules that where registered.
    registeredModules, err := cgobind.RegisteredModules(handle)
    if err != nil {
	log.Fatalln(err)
        return
    }
    defer cgobind.DlClose(handle)

    for _, name := range registeredModules {
       if name != "{{.Package}}" {
           continue
       }

       // Obtain the module.
       module, err := cgobind.InitModule(handle, name)
       if err != nil {
           log.Fatalln(err)
           return
       }

	fn_table := module.m_fn_table
	functions := cgobind.CPtr2Array(fn_table.m_functions, fn_table.m_size)
	for index := 0; index < int(fn_table.m_size); index++ {
		function := functions[index]
		functionName := C.GoString(function.m_name)

                exportedFunctions[functionName] = function

		// sym, err := DlSym(handle, "gtype2str")
		// if err != nil {
                // log.Fatalln(err)
		// 	return
		// }

		// C.call_gtype2str(sym, function.m_return_type.m_type)
		// go_str := C.GoString(rt_str)

		// util.Logf("Return type: %T", function.m_return_type.m_type)

		// util.Logf("Calling function[%d]: %s", index, functionName)
		// C.call_void_func(unsafe.Pointer(function.m_fn))
	}
    }

}

{{range .Functions}}
func {{.Name}}({{.Params}}) {{.ReturnType}} {
    // Load the shared library handle.

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
	Package     string
	LibraryPath string
	Functions   []FunctionData
}

// Struct TemplateContext:
type TemplateContext struct {
	Module      *C.GobindModule    ``
	LibraryPath string             ``
	File        *os.File           ``
	Tmpl        *template.Template ``
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

		functions[index] = FunctionData{functionName, "", "error"}
	}

	return functions
}

func (this *TemplateContext) ExtractTemplateData() TemplateData {
	moduleName := C.GoString(this.Module.m_name)
	libraryPath := this.LibraryPath
	functionData := this.ExtractFunctionData()

	return TemplateData{moduleName, libraryPath, functionData}
}

func (this *TemplateContext) Write() error {
	data := this.ExtractTemplateData()

	return this.Tmpl.Execute(this.File, data)
}

func (this *TemplateContext) Close() {
	this.File.Close()
}

// Factory functions TemplateContext:
func newTemplateContext(t_module *C.GobindModule, t_libraryPath string, t_modulePath string) (TemplateContext, error) {
	// Create the golang module file.
	moduleFile, err := os.Create(t_modulePath)
	if err != nil {
		return TemplateContext{}, err
	}

	// Create the template context.
	ctx := TemplateContext{t_module, t_libraryPath, moduleFile, nil}
	ctx.Tmpl, err = template.New(t_modulePath).Parse(MODULE_TEMPLATE)
	if err != nil {
		return ctx, err
	}

	return ctx, nil
}

// Functions:
// TODO: We also need the library path in order to understand where to depend on.
// After we have generated the library.
func generate(t_module *C.GobindModule, t_libraryPath string, t_modulePath string) error {
	util.Logf("Library path: %s", t_libraryPath)
	util.Logf("Module path: %s", t_modulePath)

	ctx, err := newTemplateContext(t_module, t_libraryPath, t_modulePath)
	if err != nil {
		return err
	}
	defer ctx.Close()

	return ctx.Write()

	// return nil
}
