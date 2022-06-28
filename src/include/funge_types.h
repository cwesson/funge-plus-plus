/**
 * @file funge_types.h
 * Common types.
 * @author Conlan Wesson
 */

#pragma once

#include <cstdint>

namespace Funge {

typedef int64_t dim_t;   ///< Type for Vectors.
typedef int64_t stack_t; ///< Type for Stacks.
typedef stack_t inst_t;  ///< Type for fungespace cells.

/**
 * Funge environment flags.
 */
enum EnvFlags{
	ENV_CONCURRENT    = 0b00001, ///< Concurrent execution (`t`) enabled.
	ENV_FILE_IN       = 0b00010, ///< File input (`i`) enabled.
	ENV_FILE_OUT      = 0b00100, ///< File output (`o`) enabled.
	ENV_EXECUTE       = 0b01000, ///< External execution (`=`) enabled.
	ENV_UNBUFFERED_IO = 0b10000, ///< Unbuffered I/O in use.
};

/**
 * External execution type.
 */
enum OperatingParadigm {
	OP_UNAVAILABLE, ///< External execution disabled.
	OP_SYSTEM,      ///< External execution as system() call.
	OP_SHELL,       ///< External execution as shell script.
	OP_FUNGE,       ///< External execution as funge.
};

/**
 * File I/O modes.
 */
enum FileFlags {
	FILE_IN_BINARY = 0b1, ///< Input files (`i`) as binary.
	FILE_OUT_TEXT  = 0b1, ///< Output files (`o`) as text.
};

/**
 * Fungespace topology.
 */
enum FungeTopo {
	TOPO_TORUS, ///< Torus topology, default for Befunge-93.
	TOPO_LAHEY, ///< Lahey topology, default for Funge-98.
};

/**
 * String mode type.
 */
enum FungeString {
	STRING_MULTISPACE, ///< Multispace strings, default for Befunge-93.
	STRING_SGML,       ///< SGML-style strings, default for Funge-98.
	STRING_C,          ///< C-style string, Funge++ extension.
};

/**
 * Fungespace cell type.
 */
enum FungeCell {
	CELL_CHAR = sizeof(char),    ///< 1 Byte cells, default for Befunge-93.
	CELL_INT  = sizeof(stack_t), ///< 8 Byte cells, default for Funge-98
};

/**
 * Threading type.
 */
enum FungeThread {
	THREAD_FUNGE,  ///< Funge-style threading, default.
	THREAD_NATIVE, ///< Native OS threading, Funge++ extension.
};

/**
 * Error codes.
 */
enum FungeError {
	ERROR_NONE,     ///< No error.
	ERROR_SKIP,     ///< Skip instruction.
	ERROR_BLOCK,    ///< Instruction blocked.
	ERROR_UNIMP,    ///< Unimplemented unstruction.
	ERROR_NOTAVAIL, ///< Feature not available.
	ERROR_UNSPEC,   ///< General execution error.
};

}
