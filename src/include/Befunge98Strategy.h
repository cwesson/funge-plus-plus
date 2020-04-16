/**
 * @file Befunge98Strategy.h
 * Strategy for Befunge-98 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "Unefunge98Strategy.h"

namespace Funge {

class Befunge98Strategy : public Unefunge98Strategy {
	public:
		Befunge98Strategy(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~Befunge98Strategy() = default;
		
		virtual bool execute(inst_t cmd);
};

}
