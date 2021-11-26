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
	.fingerprints = {},
	.dimensions = 0,
	.standard = FUNGE_98,
	.topo = TOPO_LAHEY,
	.strings = STRING_SGML,
	.cells = CELL_INT,
	.threads = THREAD_FUNGE,
	.debug = false,
	.concurrent = true,
	.execute = true,
	.filesystem = true,
	.fingerprint = true,
	.hovermode = false,
	.invertmode = false,
	.queuemode = false,
	.switchmode = false,
	.inverthl = false,
};

}
