/**
 * @file FungeDebugger.h
 * Funge Debugger.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeRunner.h"
#include "Field.h"
#include <set>
#include <map>
#include <mutex>
#include <list>

namespace Funge {

class FungeDebugger {
	public:
		FungeDebugger();
		~FungeDebugger() = default;

		void tick(FungeRunner& runner);
		void write(Field& field, const Vector& pos, inst_t inst);
		void swbreak(FungeRunner& runner);
		void addBreakpoint(const Vector& vec);
		void addWatchpoint(const Vector& vec);
	
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
			FungeRunner* runner;
			InstructionPointer* ip;
			const StackStack* stack;
			std::list<Vector> backtrace;
			State state;
		};
		
		void intro(FungeRunner& runner);
		void debug(FungeRunner* runner);
		void debugWrite(const Field& field, const Vector& pos, inst_t inst);
		void printIP(const InstructionPointer* ip);
		void printField(const Field& field, const Vector& center, const Vector& size, const Vector& dim, const InstructionPointer* ip);
		
		std::set<Vector> breakpoints;
		std::set<Vector> watchpoints;
		std::map<size_t, Thread> threads;
		std::recursive_mutex mutex;
		size_t lastThread;
};

}
