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
#include <mutex>

namespace Funge {
class FungeUniverse;

class FungeRunner {
	public:
		FungeRunner(FungeUniverse& uni, const Vector& pos, const Vector& delta);
		FungeRunner(FungeUniverse& uni, const Vector& pos, const Vector& delta, FungeRunner& r);
		FungeRunner(const FungeRunner& runner);
		FungeRunner operator=(const FungeRunner& orig) = delete;
		virtual ~FungeRunner();
		
		bool isRunning() const;
		
		void setState(FungeState& s);
		FungeState& getNormalState();
		FungeState& getStringState(inst_t i='\"');
		
		void operator()();
		void tick();
		FungeError execute(inst_t i);
		void push(stack_t n);
		
		size_t getID() const;
		FungeUniverse& getUniverse();
		Field& getField();
		StackStack& getStack();
		InstructionPointer& getIP();
		const InstructionPointer& getIP()const;
		bool isMode(FungeMode m) const;
		void setMode(FungeMode m);
		FungeMode getMode() const;
		void setUniverse(FungeUniverse& other);

		void pushSemantic(inst_t i, FungeSemantic* func);
		void pushSemantic(inst_t i, std::function<FungeError()> func, FungeSemantic::SemanticFlags flg = FungeSemantic::NONE);
		FungeSemantic* popSemantic(inst_t i);
		FungeSemantic* getSemantic(inst_t i);
		void setErrorHandler(std::function<FungeError(FungeError)> func);

		void shareStack(FungeRunner& other);
		const FungeRunner* getParent();
	
	private:
		static size_t count;

		size_t id;
		FungeUniverse* universe;
		std::shared_ptr<StackStack> stack;
		InstructionPointer ip;
		const FungeRunner* parent;
		std::function<FungeError(FungeError)> errorHandler;
		std::vector<FungeStrategy*> strategies;
		std::mutex mutex;
		
		FungeStateNormal normalState;
		FungeStateString stringState;
		FungeState* state;
		
		void run();
		void loadStrategies();
		void load(FungeStrategy* strategy);
};

}
