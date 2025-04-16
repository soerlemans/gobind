#ifndef GTYP2GO_H
#define GTYP2GO_H

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

#endif // GTYP2GO_H
