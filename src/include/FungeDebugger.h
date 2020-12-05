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
#include <list>

namespace Funge {

class FungeDebugger {
	public:
		static FungeDebugger* getInstance();
		static void tick(const Field& field, const StackStack& stack, InstructionPointer& ip);
		static void write(const Field& field, const Vector& pos, inst_t inst);
	
	private:
		enum State {
			STATE_START,
			STATE_RUN,
			STATE_STEP,
			STATE_BREAK,
		};
		
		enum {
			MAX_BACKTRACE = 10
		};
		
		struct Thread {
			InstructionPointer* ip;
			const StackStack* stack;
			std::list<Vector> backtrace;
			State state;
		};
		
		static FungeDebugger* instance;
		
		FungeDebugger();
		~FungeDebugger();
		
		void debug(const Field& field, const StackStack& stack, InstructionPointer& ip);
		void debugWrite(const Field& field, const Vector& pos, inst_t inst);
		void printIP(const InstructionPointer& ip);
		void printField(const Field& field, const Vector& center, const Vector& size);
		
		std::set<Vector> breakpoints;
		std::set<Vector> watchpoints;
		std::map<size_t, Thread> threads;
		std::mutex mutex;
		size_t lastThread;
};

}
