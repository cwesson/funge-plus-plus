/**
 * @file FungeStrategy.h
 * Strategy for executing Funge commands.
 * @author Conlan Wesson
 */

#pragma once

#include "Field.h"
#include "InstructionPointer.h"
#include "StackStack.h"

namespace Funge {

class FungeStrategy {
	public:
		FungeStrategy(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~FungeStrategy() = default;
		
		virtual bool execute(inst_t cmd) = 0;
	
	protected:
		Field& field;
		InstructionPointer& ip;
		StackStack& stack;
};

}
