/**
 * @file FungeConfig.cpp
 * Configuration items for the interpreter.
 * @Conlan Wesson
 */

#pragma once

#include <cstddef>

namespace Funge {

struct FungeConfig {
	size_t dimensions;
	unsigned int standard;
	bool concurrent;
	bool execute;
	bool filesystem;
};

extern struct FungeConfig funge_config;

}
