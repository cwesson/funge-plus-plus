/**
 * @file FungeConfig.cpp
 * Configuration items for the interpreter.
 * @Conlan Wesson
 */

#pragma once

#include "funge_types.h"
#include <cstddef>
#include <vector>
#include <string>

namespace Funge {

enum FungeMode {
	// Suppress Summary 0x00200,
	FUNGE_MODE_DEBUG  = 0x00400,
	// Trace Mode       0x00800,
	// Rc/Funge-98 y    0x01000,
	FUNGE_MODE_HOVER  = 0x02000,
	FUNGE_MODE_INVERT = 0x04000,
	FUNGE_MODE_QUEUE  = 0x08000,
	FUNGE_MODE_SWITCH = 0x10000
};

class FungeConfig {
	public:
		std::string name;
		std::vector<std::string> args;
		std::vector<std::string> env;
		std::vector<uint64_t> fingerprints;
		size_t dimensions;
		unsigned int standard;
		FungeTopo topo;
		FungeString strings;
		FungeCell cells;
		FungeThread threads;
		unsigned int mode;
		bool concurrent;
		bool execute;
		bool filesystem;
		bool fingerprint;
		bool inverthl;

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
