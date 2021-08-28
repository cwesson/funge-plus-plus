/**
 * @file Trefunge98Strategy.h
 * Strategy for Trefunge-98 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeStrategy.h"

namespace Funge {

class Trefunge98Strategy : public FungeStrategy {
	public:
		Trefunge98Strategy(Field& f, InstructionPointer& i, StackStack& s, FungeRunner& r);
		virtual ~Trefunge98Strategy() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
