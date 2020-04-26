/**
 * @file FungeConfig.cpp
 * Configuration items for the interpreter.
 * @Conlan Wesson
 */

#include "FungeConfig.h"

namespace Funge {

struct FungeConfig funge_config = {
	.args = {},
	.env = {},
	.dimensions = 0,
	.standard = 98,
	.concurrent = true,
	.execute = true,
	.filesystem = true,
	.fingerprint = true,
};

}
