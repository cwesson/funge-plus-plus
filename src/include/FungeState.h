/**
 * @file FungeState.h
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#pragma once

#include "StackStack.h"
#include "InstructionPointer.h"

namespace Funge {
class FungeRunner;

class FungeState {
	public:
		FungeState(FungeRunner& r);
		virtual ~FungeState() = default;
		
		virtual bool execute(inst_t i) = 0;
	
	protected:
		FungeRunner& runner;
		StackStack& stack;
		InstructionPointer& ip;
};

}
