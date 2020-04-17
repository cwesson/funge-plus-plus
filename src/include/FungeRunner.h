/**
 * @file FungeRunner.h
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#pragma once

#include "Field.h"
#include "StackStack.h"
#include "InstructionPointer.h"
#include "FungeStateNormal.h"
#include "FungeStateString.h"
#include <thread>

namespace Funge {
class FungeState;

class FungeRunner {
	public:
		explicit FungeRunner(Field& f);
		FungeRunner(Field& f, const StackStack& s, const InstructionPointer& i);
		
		void join() const;
		
		void setState(FungeState& s);
		FungeState& getNormalState();
		FungeState& getStringState();
		
		void operator()();
	
	private:
		Field& field;
		StackStack stack;
		InstructionPointer ip;
		std::thread* thread;
		
		FungeStateNormal normalState;
		FungeStateString stringState;
		FungeState* state;
		
		void run();
};

}
