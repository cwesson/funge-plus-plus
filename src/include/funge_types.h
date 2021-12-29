/**
 * @file funge_types.h
 * Common types.
 * @author Conlan Wesson
 */

#pragma once

#include <cstdint>
#include <cstddef>

namespace Funge {

typedef int64_t dim_t;
typedef int64_t inst_t;
typedef int64_t stack_t;

enum EnvFlags{
	ENV_CONCURRENT    = 0b00001,
	ENV_FILE_IN       = 0b00010,
	ENV_FILE_OUT      = 0b00100,
	ENV_EXECUTE       = 0b01000,
	ENV_UNBUFFERED_IO = 0b10000,
};

enum OperatingParadigm {
	OP_UNAVAILABLE,
	OP_SYSTEM,
	OP_SHELL,
	OP_FUNGE,
};

enum FileFlags {
	FILE_IN_BINARY = 0b1,
	FILE_OUT_TEXT  = 0b1,
};

enum FungeTopo {
	TOPO_TORUS,
	TOPO_LAHEY,
};

enum FungeString {
	STRING_MULTISPACE,
	STRING_SGML,
	STRING_C,
};

enum FungeCell {
	CELL_CHAR = sizeof(char),
	CELL_INT  = sizeof(inst_t),
};

enum FungeThread {
	THREAD_NATIVE,
	THREAD_FUNGE,
};

}
