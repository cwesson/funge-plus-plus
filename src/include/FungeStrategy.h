/**
 * @file FungeStrategy.h
 * Strategy for executing Funge commands.
 * @author Conlan Wesson
 */

#pragma once

#include "Field.h"
#include "InstructionPointer.h"
#include "StackStack.h"
#include "FungeState.h"
#include <random>

namespace Funge {

class FungeStrategy {
	public:
		FungeStrategy(Field& f, InstructionPointer& i, StackStack& s, FungeState& t, std::initializer_list<inst_t> in);
		virtual ~FungeStrategy() = default;
		
		virtual bool execute(inst_t cmd) = 0;
		
		const std::vector<inst_t>& instructions() const;
	
	protected:
		Field& field;
		InstructionPointer& ip;
		StackStack& stack;
		FungeState& state;
		
		stack_t random(stack_t min, stack_t max);
	
	private:
		std::random_device rd;
		std::mt19937 gen;
		std::vector<inst_t> inst;
};

}
