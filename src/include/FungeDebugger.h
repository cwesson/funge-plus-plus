/**
 * @file FungeDebugger.h
 * Funge Debugger.
 * @author Conlan Wesson
 */

#pragma once

#include "Field.h"
#include "StackStack.h"
#include "InstructionPointer.h"
#include <set>
#include <map>
#include <mutex>

namespace Funge {

class FungeDebugger {
	public:
		static FungeDebugger* getInstance();
		static void tick(const Field& field, const StackStack& stack, const InstructionPointer& ip);
	
	private:
		enum State {
			STATE_START,
			STATE_RUN,
			STATE_STEP,
			STATE_BREAK,
		};
		
		struct Thread {
			const InstructionPointer* ip;
			const StackStack* stack;
			State state;
		};
		
		static FungeDebugger* instance;
		
		FungeDebugger();
		~FungeDebugger();
		
		void debug(const Field& field, const StackStack& stack, const InstructionPointer& ip);
		void printIP(const InstructionPointer& ip);
		void printField(const Field& field, const Vector& center, const Vector& size);
		
		std::set<Vector> breakpoints;
		std::map<size_t, Thread> threads;
		std::mutex mutex;
};

}
