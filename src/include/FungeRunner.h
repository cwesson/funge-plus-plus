/**
 * @file FungeRunner.h
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#pragma once

#include "StackStack.h"
#include "InstructionPointer.h"
#include "FungeState.h"
#include "FungeStateNormal.h"
#include "FungeStateString.h"
#include "FungeConfig.h"
#include <memory>

namespace Funge {
class FungeUniverse;

class FungeRunner {
	public:
		FungeRunner(FungeUniverse& uni, const Vector& pos, const Vector& delta);
		FungeRunner(FungeUniverse& uni, const Vector& pos, const Vector& delta, FungeRunner& r);
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
		bool isMode(FungeMode m) const;
		stack_t getMode() const;
		void setUniverse(FungeUniverse& other);

		void pushSemantic(inst_t i, semantic_t func);
		semantic_t popSemantic(inst_t i);
		semantic_t getSemantic(inst_t i);

		void shareStack(FungeRunner& other);
	
	private:
		FungeUniverse* universe;
		std::shared_ptr<StackStack> stack;
		InstructionPointer ip;
		
		FungeStateNormal normalState;
		FungeStateString stringState;
		FungeState* state;
		
		void run();
};

}
