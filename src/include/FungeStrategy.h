/**
 * @file FungeStrategy.h
 * Strategy for executing Funge commands.
 * @author Conlan Wesson
 */

#pragma once

#include "Field.h"
#include "InstructionPointer.h"
#include "StackStack.h"
#include <functional>
#include <random>

namespace Funge {

class FungeRunner;

class FungeStrategy {
	public:
		FungeStrategy(FungeRunner& r);
		virtual ~FungeStrategy() = default;
		
		virtual bool operator()(inst_t cmd) = 0;
		virtual FungeStrategy* clone(FungeRunner& r) const = 0;
	
	protected:
		FungeRunner& runner;
		Field& field;
		InstructionPointer& ip;
		StackStack& stack;
		
		stack_t random(stack_t min, stack_t max);
	
	private:
		std::default_random_engine rd;
		std::mt19937 gen;
};

}
