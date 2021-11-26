/**
 * @file FungeConfig.cpp
 * Configuration items for the interpreter.
 * @Conlan Wesson
 */

#pragma once

#include <cstddef>
#include <vector>
#include <string>

namespace Funge {

enum FungeStandard {
	FUNGE_93 = 93,
	FUNGE_98 = 98,
	FUNGE_FISH = -1,
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
	CELL_CHAR,
	CELL_INT,
};

enum FungeThread {
	THREAD_NATIVE,
	THREAD_FUNGE,
};

struct FungeConfig {
	std::vector<std::string> args;
	std::vector<std::string> env;
	std::vector<uint64_t> fingerprints;
	size_t dimensions;
	FungeStandard standard;
	FungeTopo topo;
	FungeString strings;
	FungeCell cells;
	FungeThread threads;
	bool debug;
	bool concurrent;
	bool execute;
	bool filesystem;
	bool fingerprint;
	bool hovermode;
	bool invertmode;
	bool queuemode;
	bool switchmode;
	bool inverthl;
};

extern struct FungeConfig funge_config;

}
