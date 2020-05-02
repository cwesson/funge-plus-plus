/**
 * @file FungeStrategy.h
 * Strategy for executing Funge commands.
 * @author Conlan Wesson
 */

#pragma once

#include "Field.h"
#include "InstructionPointer.h"
#include "StackStack.h"
#include <random>

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
		
		stack_t random();
	
	private:
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<stack_t> dis;
};

}
