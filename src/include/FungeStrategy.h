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

class FungeRunner;

class FungeStrategy {
	public:
		FungeStrategy(Field& f, InstructionPointer& i, StackStack& s, FungeRunner& r, std::initializer_list<inst_t> in);
		virtual ~FungeStrategy() = default;
		
		virtual bool execute(inst_t cmd) = 0;
		
		const std::vector<inst_t>& instructions() const;
	
	protected:
		Field& field;
		InstructionPointer& ip;
		StackStack& stack;
		FungeRunner& runner;
		
		stack_t random(stack_t min, stack_t max);
	
	private:
		std::default_random_engine rd;
		std::mt19937 gen;
		std::vector<inst_t> inst;
};

}
