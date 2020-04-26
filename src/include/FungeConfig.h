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

struct FungeConfig {
	std::vector<std::string> args;
	std::vector<std::string> env;
	size_t dimensions;
	unsigned int standard;
	bool concurrent;
	bool execute;
	bool filesystem;
	bool fingerprint;
};

extern struct FungeConfig funge_config;

}
