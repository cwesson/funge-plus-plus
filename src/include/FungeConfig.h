/**
 * @file FungeConfig.cpp
 * Configuration items for the interpreter.
 * @author Conlan Wesson
 */

#pragma once

#include "funge_types.h"
#include <cstddef>
#include <vector>
#include <string>

namespace Funge {

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
};

/**
 * Funge configuration.
 */
class FungeConfig {
	public:
		std::string name;                   ///< Universe name.
		std::vector<std::string> args;      ///< Command line arguments.
		std::vector<std::string> env;       ///< Environment variables.
		std::vector<uint64_t> fingerprints; ///< Fingerprints to load.
		size_t dimensions;                  ///< Number of dimensions.
		unsigned int standard;              ///< Funge standard.
		FungeTopo topo;                     ///< Fungespace topology.
		FungeString strings;                ///< String mode style.
		FungeCell cells;                    ///< Fungespace cell type.
		FungeThread threads;                ///< Threading style.
		unsigned int mode;                  ///< FungeMode flags.
		bool concurrent;                    ///< Allow concurrent execution (`t`).
		bool execute;                       ///< Allow external execution (`=`).
		bool filesystem;                    ///< Allow filesystem access (`i` and `o`).
		bool fingerprint;                   ///< Allow fingerprints.
		bool inverthl;                      ///< Invert `h` and `l`.  @see README.md Errata.

		/**
		 * Constructor.
		 */
		FungeConfig() :
			name(""),
			args(),
			env(),
			fingerprints(),
			dimensions(0),
			standard(98),
			topo(TOPO_LAHEY),
			strings(STRING_SGML),
			cells(CELL_INT),
			threads(THREAD_FUNGE),
			mode(0),
			concurrent(true),
			execute(true),
			filesystem(true),
			fingerprint(true),
			inverthl(false)
		{}
};

}
