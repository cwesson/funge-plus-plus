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

namespace Funge {
class FungeState;

class FungeRunner {
	public:
		explicit FungeRunner(Field& f);
		FungeRunner(Field& f, const StackStack& s, const InstructionPointer& i);
		
		size_t getID() const;
		bool isRunning() const;
		
		void setState(FungeState& s);
		FungeState& getNormalState();
		FungeState& getStringState();
		
		void operator()();
		void tick();
	
	private:
		static size_t count;
		size_t id;
		Field& field;
		StackStack stack;
		InstructionPointer ip;
		
		FungeStateNormal normalState;
		FungeStateString stringState;
		FungeState* state;
		
		void run();
};

}
