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

import (
	"os"
	"path/filepath"
	"text/template"

	_ "embed"
	_ "github.com/soerlemans/gobind/src/lib/cgobind"
	util "github.com/soerlemans/gobind/src/lib/go_util"
)

// TODO: Figure this out.
// #cgo CFLAGS: -I {{OutputDir}}/include/

//go:embed module.go.tmpl
var MODULE_TEMPLATE string

// Structs:
type FunctionData struct {
	Name       string
	Params     string
	ReturnType string
}

type TemplateData struct {
	Package     string
	LibraryDir  string
	LibraryName string
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

func (this *TemplateContext) ExtractTemplateData() (TemplateData, error) {
	var data TemplateData

	// Get the absolute path of the library.
	absPath, err := filepath.Abs(this.LibraryPath)
	if err != nil {
		return data, err
	}

	data.Package = C.GoString(this.Module.m_name)
	data.LibraryDir = filepath.Dir(absPath)
	data.LibraryName = filepath.Base(absPath)
	data.Functions = this.ExtractFunctionData()

	return data, err
}

func (this *TemplateContext) Write() error {
	data, err := this.ExtractTemplateData()
	if err != nil {
		return err
	}

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
