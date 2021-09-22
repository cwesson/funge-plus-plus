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
		FungeRunner(const FungeRunner& runner);
		virtual ~FungeRunner();
		
		bool isRunning() const;
		
		void setState(FungeState& s);
		FungeState& getNormalState();
		FungeState& getStringState();
		
		void operator()();
		void tick();
		bool execute(inst_t i);
		
		FungeUniverse& getUniverse();
		Field& getField();
		StackStack& getStack();
		InstructionPointer& getIP();

		void setSemantic(inst_t i, std::function<bool()> func);
		void popSemantic(inst_t i);
	
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
