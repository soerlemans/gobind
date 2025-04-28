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
	"strings"
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
// Contains all data necessary to create 
type ParameterData struct {
	Name string
	Type string
}

// Contains all data necessary to create a wrapper for a function.
type FunctionData struct {
	Name       string `Name of the function.`
	Params     string `Parameters`
	ReturnType string `Golang return type of the function.`
}

// Contains toplevel data for the Golang template module.
type TemplateData struct {
	Package     string `Golang package name to use.`
	LibraryDir  string `Directory to add to the linker path using -L.`
	LibraryName string `Library name to link against using -l.`
	Functions   []FunctionData `Looped through to create the wrapper functions.`
}

// Struct TemplateContext:
// Contains all the context needed for executing the wrapper module template.
type TemplateContext struct {
	Module      *C.GobindModule    `GobindModule struct to unpack and create bindings for.`
	LibraryPath string             `Absolute path to the library.`
	File        *os.File           `File to execute template to.`
	Tmpl        *template.Template `Store the template in memory.`
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

	libraryDir := filepath.Dir(absPath)

	// Get base path and trim lib and .so.
	libraryName := filepath.Base(absPath)
	trimmed := strings.TrimPrefix(libraryName, "lib")
	trimmed = strings.TrimSuffix(trimmed, ".so")

	data.Package = C.GoString(this.Module.m_name)
	data.LibraryDir = libraryDir
	data.LibraryName = trimmed
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
