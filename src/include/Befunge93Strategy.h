/**
 * @file Befunge93Strategy.h
 * Strategy for Befunge-93 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "Unefunge93Strategy.h"

namespace Funge {

class Befunge93Strategy : public Unefunge93Strategy {
	public:
		Befunge93Strategy(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~Befunge93Strategy() = default;
		
		virtual bool execute(inst_t cmd);
};

}
