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
		FungeState(FungeRunner& r, StackStack& s, InstructionPointer& i);
		virtual ~FungeState() = default;
		
		virtual bool execute(inst_t i) = 0;
		
		FungeRunner& getRunner();
	
	protected:
		FungeRunner& runner;
		StackStack& stack;
		InstructionPointer& ip;
};

}
