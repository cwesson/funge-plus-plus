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

enum FungeStandard {
	FUNGE_AUTO = 0,
	FUNGE_93 = 93,
	FUNGE_98 = 98,
	FUNGE_FISH = -1,
	FUNGE_STARFISH = -2,
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
		FungeStandard standard;             ///< Funge standard.
		FungeTopo topo;                     ///< Fungespace topology.
		FungeString strings;                ///< String mode style.
		FungeCell cells;                    ///< Fungespace cell type.
		FungeThread threads;                ///< Threading style.
		FungeMode mode;                     ///< FungeMode flags.
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
			standard(FUNGE_AUTO),
			topo(TOPO_LAHEY),
			strings(STRING_SGML),
			cells(CELL_INT),
			threads(THREAD_FUNGE),
			mode(),
			concurrent(true),
			execute(true),
			filesystem(true),
			fingerprint(true),
			inverthl(false)
		{}
};

}
