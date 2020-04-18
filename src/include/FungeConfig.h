/**
 * @file FungeConfig.cpp
 * Configuration items for the interpreter.
 * @Conlan Wesson
 */

#include <cstddef>

namespace Funge {

struct FungeConfig {
	size_t dimensions;
	unsigned int standard;
	bool concurrent;
	bool filesystem;
};

extern struct FungeConfig funge_config;

}
