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
#include "FungeUniverse.h"

namespace Funge {
class FungeState;

class FungeRunner {
	public:
		FungeRunner(FungeUniverse& uni);
		FungeRunner(FungeUniverse& uni, const FungeRunner& runner);
		virtual ~FungeRunner();
		
		bool isRunning() const;
		
		void setState(FungeState& s);
		FungeState& getNormalState();
		FungeState& getStringState();
		
		void operator()();
		void tick();
		
		FungeUniverse& getUniverse();
	
	private:
		FungeUniverse& universe;
		Field& field;
		StackStack stack;
		InstructionPointer ip;
		
		FungeStateNormal normalState;
		FungeStateString stringState;
		FungeState* state;
		
		void run();
};

}
