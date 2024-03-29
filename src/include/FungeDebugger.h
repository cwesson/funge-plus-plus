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
		explicit FungeDebugger(FungeUniverse& uni);
		~FungeDebugger() = default;

		void tick(FungeRunner& runner);
		void swbreak(FungeRunner& runner);
		void trap(FungeRunner& runner);
		void addBreakpoint(const Vector& vec);
		void addWatchpoint(const Vector& vec);
		void endThread(const FungeRunner& runner);
	
	private:
		enum State {
			STATE_START,
			STATE_RUN,
			STATE_STEP,
			STATE_BREAK,
			STATE_END,
		};
		
		enum {
			MAX_BACKTRACE = 10
		};
		
		struct Thread {
			FungeRunner* runner;
			std::list<Vector> backtrace;
			State state;
		};
		
		void intro(FungeRunner& runner);
		void debugWrite(const Vector& pos, inst_t inst);

		FungeUniverse& universe;
		std::set<Vector> breakpoints;
		std::set<Vector> watchpoints;
		std::map<size_t, Thread> threads;
		std::recursive_mutex mutex;
		size_t lastThread;

		friend class Defunge;
};

}
