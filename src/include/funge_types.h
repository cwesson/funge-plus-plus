/**
 * @file funge_types.h
 * Common types.
 * @author Conlan Wesson
 */

#pragma once

#include <cstdint>
#include <cstdio>

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
 * Funge execution flags.
 */
enum FungeMode {
	// Suppress Summary 0x00200,
	FUNGE_MODE_DEBUG  = 0x00400, ///< Debug enabled.
	// Trace Mode       0x00800,
	// Rc/Funge-98 y    0x01000,
	FUNGE_MODE_HOVER  = 0x02000, ///< Hover mode enabled by MODE `H`
	FUNGE_MODE_INVERT = 0x04000, ///< Invert mode enabled by MODE `I`
	FUNGE_MODE_QUEUE  = 0x08000, ///< Queue mode enabled by MODE `Q`
	FUNGE_MODE_SWITCH = 0x10000, ///< Switch mode enabled by MODE `S`
	FUNGE_MODE_DIVE   = 0x20000, ///< Switch mode enabled by *><> `u`
};

inline FungeMode operator|(FungeMode a, FungeMode b)
{
	return static_cast<FungeMode>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline FungeMode operator|=(FungeMode& a, FungeMode b)
{
	a = a | b;
	return a;
}

inline FungeMode operator&(FungeMode a, FungeMode b)
{
	return static_cast<FungeMode>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}

inline FungeMode operator&=(FungeMode& a, FungeMode b)
{
	a =  a & b;
	return a;
}

inline FungeMode operator^(FungeMode a, FungeMode b)
{
	return static_cast<FungeMode>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b));
}

inline FungeMode operator^=(FungeMode& a, FungeMode b)
{
	a = a ^ b;
	return a;
}

inline FungeMode operator~(FungeMode a)
{
	return static_cast<FungeMode>(~static_cast<unsigned int>(a));
}

/**
 * Error codes.
 */
enum FungeError {
	ERROR_NONE,     ///< No error.
	ERROR_SKIP,     ///< Skip instruction.
	ERROR_BLOCK,    ///< Instruction blocked.
	ERROR_UNIMP,    ///< Unimplemented instruction.
	ERROR_NOTAVAIL, ///< Feature not available.
	ERROR_UNSPEC,   ///< General execution error.
	ERROR_DIV0,     ///< Divide by zero.
	ERROR_EMPTY,    ///< Not enough elements in stack.
	ERROR_NOSTACK,  ///< Stack does not exist.
};

}
