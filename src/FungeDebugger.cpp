/**
 * @file FungeDebugger.h
 * Funge Debugger.
 * @author Conlan Wesson
 */

#include "FungeDebugger.h"
#include "Defunge.h"
#include "FungeConfig.h"
#include "FungeMultiverse.h"
#include "FungeUniverse.h"
#include "Field.h"
#include <iostream>

namespace Funge {

FungeDebugger::FungeDebugger(FungeUniverse& uni) :
	universe(uni),
	breakpoints(),
	watchpoints(),
	threads(),
	mutex(),
	lastThread(0)
{
}

void FungeDebugger::tick(FungeRunner& runner){
	if(runner.isMode(FUNGE_MODE_DEBUG)){
		intro(runner);
		size_t id = runner.getID();
		auto found = threads.find(id);
		if(found == threads.end()){
			threads.insert({id, Thread{
				.runner = &runner,
				.backtrace = {},
				.state = FungeDebugger::STATE_START,
			}});
			std::cout << "New IP " << id << std::endl;
		}
		lastThread = id;
		
		const InstructionPointer& ip = runner.getIP();
		if(breakpoints.contains(ip.getPos())){
			std::cout << "Breakpoint " << ip.getPos() << std::endl;
			threads[id].state = FungeDebugger::STATE_BREAK;
		}
		
		if(threads[id].backtrace.size() >= FungeDebugger::MAX_BACKTRACE){
			threads[id].backtrace.pop_back();
		}
		threads[id].backtrace.push_front(ip.getPos());
		Defunge::getInstance().debug(this, &runner);
	}
}
void FungeDebugger::swbreak(FungeRunner& runner){
	if(runner.isMode(FUNGE_MODE_DEBUG)){
		intro(runner);
		std::cout << "Software Breakpoint " << runner.getIP().getPos() << std::endl;
		threads[lastThread].state = STATE_BREAK;
		Defunge::getInstance().debug(this, &runner);
	}
}

void FungeDebugger::trap(FungeRunner& runner){
	if(runner.isMode(FUNGE_MODE_DEBUG)){
		intro(runner);
		std::cout << "Exception Trapped " << runner.getIP().getPos() << std::endl;
		threads[lastThread].state = STATE_BREAK;
		Defunge::getInstance().debug(this, &runner);
	}
}

void FungeDebugger::debugWrite(const Vector& pos, inst_t inst){
	if(universe.isMode(FUNGE_MODE_DEBUG)){
		if(watchpoints.contains(pos)){
			threads[lastThread].state = STATE_BREAK;
			intro(*threads[lastThread].runner);
			std::cout << "Watchpoint " << pos << std::endl;
			inst_t old = universe.getField().get(pos);
			std::cout << "Old value = (" << old  << ") \"" << static_cast<char>(old) << "\"" << std::endl;
			std::cout << "New value = (" << inst << ") \"" << static_cast<char>(inst) << "\"" << std::endl;
			Defunge::getInstance().debug(this, threads[lastThread].runner);
		}
	}
}

void FungeDebugger::addBreakpoint(const Vector& vec){
	if(vec.size() > 0){
		std::lock_guard<std::recursive_mutex> guard(mutex);
		breakpoints.insert(vec);
	}
}

void FungeDebugger::addWatchpoint(const Vector& vec){
	if(vec.size() > 0){
		if(watchpoints.empty()){
			universe.getField().addObserver(std::bind(&FungeDebugger::debugWrite, this, std::placeholders::_1, std::placeholders::_2));
		}
		std::lock_guard<std::recursive_mutex> guard(mutex);
		watchpoints.insert(vec);
	}
}

void FungeDebugger::endThread(const FungeRunner& runner){
	threads[runner.getID()].state = STATE_END;
}

void FungeDebugger::intro(FungeRunner& runner){
	static bool first = true;

	if(first){
		std::cout << "Funge++ Debugger" << std::endl;
		for(auto arg : runner.getUniverse().arguments()){
			std::cout << arg << " ";
		}
		std::cout << std::endl;
		first = false;
	}
}

}
