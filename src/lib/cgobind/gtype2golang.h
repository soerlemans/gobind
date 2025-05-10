#ifndef GTYPE2GOLANG_H
#define GTYPE2GOLANG_H

/*!
 * @file
 */

// Library Includes:
#include <gobind/gobind.h>

// Functions:
//! Convert a @ref GType to a Golang native type.
const char* gtype2golang(GType t_gtype);

//! Convert a @ref GType to a Golang cgo type.
const char* gtype2cgotype(GType t_gtype);

#endif // GTYPE2GOLANG_H
