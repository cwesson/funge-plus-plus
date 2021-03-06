/**
 * @file FungeStateString.h
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeState.h"

namespace Funge {

class FungeStateString : public FungeState {
	public:
		FungeStateString(FungeRunner& r, StackStack& s, InstructionPointer& i);
		virtual ~FungeStateString() = default;
		
		virtual bool execute(inst_t i) override;
	private:
		void escape(inst_t i);
		
		inst_t previous;
};

}
