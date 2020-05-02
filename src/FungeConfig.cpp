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
	.topo = TOPO_LAHEY,
	.strings = STRING_SGML,
	.cells = CELL_INT,
	.threads = THREAD_FUNGE,
	.concurrent = true,
	.execute = true,
	.filesystem = true,
	.fingerprint = true,
};

}
