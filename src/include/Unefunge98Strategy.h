/**
 * @file Unefunge98Strategy.h
 * Strategy for Unefunge-98 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "Unefunge93Strategy.h"
#include "FingerprintStrategy.h"

namespace Funge {

class Unefunge98Strategy : public Unefunge93Strategy {
	public:
		Unefunge98Strategy(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~Unefunge98Strategy() = default;
		
		virtual bool execute(inst_t cmd) override;
	
	private:
		void pushSysInfo(int num);
		FingerprintStrategy finger;
};

}
