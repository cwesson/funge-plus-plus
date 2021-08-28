/**
 * @file Befunge98Strategy.h
 * Strategy for Befunge-98 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeStrategy.h"

namespace Funge {

class Befunge98Strategy : public FungeStrategy {
	public:
		Befunge98Strategy(Field& f, InstructionPointer& i, StackStack& s, FungeRunner& r);
		virtual ~Befunge98Strategy() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
