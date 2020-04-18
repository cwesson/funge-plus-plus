/**
 * @file Trefunge98Strategy.h
 * Strategy for Trefunge-98 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "Befunge98Strategy.h"

namespace Funge {

class Trefunge98Strategy : public Befunge98Strategy {
	public:
		Trefunge98Strategy(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~Trefunge98Strategy() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
