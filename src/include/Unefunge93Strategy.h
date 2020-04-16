/**
 * @file Unefunge93Strategy.h
 * Strategy for Unefunge-93 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeStrategy.h"

namespace Funge {

class Unefunge93Strategy : public FungeStrategy {
	public:
		Unefunge93Strategy(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~Unefunge93Strategy() = default;
		
		virtual bool execute(inst_t cmd);
};

}
