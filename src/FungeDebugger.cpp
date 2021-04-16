/**
 * @file FungeDebugger.h
 * Funge Debugger.
 * @author Conlan Wesson
 */

#include "FungeDebugger.h"
#include "FungeConfig.h"
#include <iostream>
#include <sstream>

namespace Funge {

FungeDebugger* FungeDebugger::instance = nullptr;

FungeDebugger::FungeDebugger() :
	breakpoints(),
	threads(),
	mutex(),
	lastThread(0)
{
	std::cout << "Funge++ Debugger" << std::endl;
	for(auto arg : funge_config.args){
		std::cout << arg << " ";
	}
	std::cout << std::endl;
}

FungeDebugger* FungeDebugger::getInstance() {
	if(instance == nullptr){
		instance = new FungeDebugger();
	}
	return instance;
}

void FungeDebugger::tick(const Field& field, const StackStack& stack, InstructionPointer& ip){
	if(funge_config.debug){
		FungeDebugger* inst = getInstance();
		inst->debug(field, stack, ip);
	}
}

void FungeDebugger::write(const Field& field, const Vector& pos, inst_t inst){
	if(funge_config.debug){
		FungeDebugger* dbg = getInstance();
		dbg->debugWrite(field, pos, inst);
	}
}

void FungeDebugger::swbreak(const Field& field, const StackStack& stack, InstructionPointer& ip){
	if(funge_config.debug){
		std::cout << "Software Breakpoint " << ip.getPos() << std::endl;
		threads[lastThread].state = STATE_BREAK;
		debug(field, stack, ip);
	}
}

void FungeDebugger::debugWrite(const Field& field, const Vector& pos, inst_t inst){
	if(watchpoints.contains(pos)){
		threads[lastThread].state = STATE_BREAK;
		std::cout << "Watchpoint " << pos << std::endl;
		inst_t old = field.get(pos);
		std::cout << "Old value = (" << old  << ") \"" << static_cast<char>(old) << "\"" << std::endl;
		std::cout << "New value = (" << inst << ") \"" << static_cast<char>(inst) << "\"" << std::endl;
		debug(field, *threads[lastThread].stack, *threads[lastThread].ip);
	}
}

void FungeDebugger::debug(const Field& field, const StackStack& stack, InstructionPointer& ip){
	std::lock_guard<std::recursive_mutex> guard(mutex);
	const size_t id = ip.getID();
	auto found = threads.find(id);
	if(found == threads.end()){
		threads.insert({id, {
			.ip = &ip,
			.stack = &stack,
			.backtrace = {},
			.state = STATE_START,
		}});
		std::cout << "New IP " << id << std::endl;
	}
	lastThread = id;
	
	if(breakpoints.contains(ip.getPos())){
		std::cout << "Breakpoint " << ip.getPos() << std::endl;
		threads[id].state = STATE_BREAK;
	}
	
	if(threads[id].backtrace.size() >= MAX_BACKTRACE){
		threads[id].backtrace.pop_back();
	}
	threads[id].backtrace.push_front(ip.getPos());
	
	switch(threads[id].state){
		case STATE_RUN:
			return;
		case STATE_START:
		case STATE_STEP:
		case STATE_BREAK:
			break;
	}
	
	printIP(ip);
	
	size_t tid = id;
	while(threads[id].state != STATE_RUN){
		std::cout << "\e[33m(defunge)\e[0m " << std::flush;
		
		std::string line;
		std::getline(std::cin, line);
		auto iss = std::istringstream(line);
		
		std::string cmd;
		iss >> cmd;
		
		if(cmd == "run" || cmd == "continue" || cmd == "con" || cmd == "c"){
			threads[tid].state = STATE_RUN;
		}else if(cmd == "quit" || cmd == "q"){
			exit(1);
		}else if(cmd == "step" || cmd == "stp" || cmd == "s"){
			threads[tid].state = STATE_STEP;
			break;
		}else if(cmd == "peek" || cmd == "p"){
			size_t c = 0;
			iss >> c;
			if(c == 0){
				for(size_t j = 0; j < threads[tid].stack->size(); ++j){
					std::cout << "[0] ";
					for(size_t i = threads[tid].stack->at(j).size(); i > 0; --i){
						std::cout << threads[tid].stack->at(j).get(i) << " ";
					}
					std::cout << std::endl;
				}
			}else{
				size_t s = 0;
				iss >> s;
				std::cout << threads[tid].stack->at(s).get(c) << std::endl;
			}
		}else if(cmd == "get" || cmd == "g"){
			Vector v;
			iss >> v;
			if(v.size() == 0){
				v = ip.getPos();
			}
			Vector s;
			iss >> s;
			if(s.size() == 0){
				s = {3,3};
			}
			Vector d;
			iss >> d;
			if(d.size() == 0){
				d = {0,1};
			}
			printField(field, v, s, d, *threads[tid].ip);
		}else if(cmd == "list" || cmd == "l"){
			Vector s;
			iss >> s;
			if(s.size() == 0){
				s = {3,3};
			}
			Vector d;
			iss >> d;
			if(d.size() == 0){
				d = {0,1};
			}
			printField(field, threads[tid].ip->getPos(), s, d, *threads[tid].ip);
		}else if(cmd == "break" || cmd == "bp"){
			Vector v;
			iss >> v;
			addBreakpoint(v);
			for(auto b : breakpoints){
				std::cout << "Breakpoint " << b << std::endl;
			}
		}else if(cmd == "watch" || cmd == "wp"){
			Vector v;
			iss >> v;
			addWatchpoint(v);
			for(auto w : watchpoints){
				std::cout << "Watchpoint " << w << std::endl;
			}
		}else if(cmd =="delta" || cmd == "dir" || cmd == "d"){
			std::cout << "Delta " << threads[tid].ip->getDelta() << std::endl;
		}else if(cmd == "storage"){
			std::cout << "Storage " << threads[tid].ip->getStorage() << std::endl;
		}else if(cmd == "position" || cmd == "pos"){
			printIP(ip);
		}else if(cmd == "thread" || cmd == "t"){
			const size_t old = tid;
			iss >> tid;
			if(tid == old){
				for(auto t : threads){
					printIP(*(t.second.ip));
				}
			}else{
				printIP(*threads[tid].ip);
			}
		}else if(cmd == "backtrace" || cmd == "bt"){
			std::cout << "Backtrace" << std::endl;
			size_t i = 0;
			for(auto b : threads[tid].backtrace){
				std::cout << "#" << i++ << "  " << b << " \"" << static_cast<char>(field.get(b)) << "\"" << std::endl;
			}
		}else if(cmd == "setdelta"){
			Vector v;
			iss >> v;
			threads[tid].ip->setDelta(v);
			std::cout << "Delta " << threads[tid].ip->getDelta() << std::endl;
		}else if(cmd == "setpos"){
			Vector v;
			iss >> v;
			threads[tid].ip->setPos(v);
			printIP(ip);
		}else if(cmd == "read"){
			Vector v;
			iss >> v;
			inst_t i = field.get(v);
			std::cout << "Value = (" << i << ") \"" << static_cast<char>(i) << "\"" << std::endl;
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
		std::lock_guard<std::recursive_mutex> guard(mutex);
		watchpoints.insert(vec);
	}
}

void FungeDebugger::printIP(const InstructionPointer& ip){
	std::cout << ip.getID() << ": " << ip.getPos() << " \"" << static_cast<char>(ip.get()) << "\"" << std::endl;
}

void FungeDebugger::printField(const Field& field, const Vector& center, const Vector& size, const Vector& dim, const InstructionPointer& ip){
	const Vector start = center-size;
	const Vector end = center+size;
	Vector pos = start;
	while(pos <= end){
		inst_t i = field.get(pos);
		bool color = false;
		for(auto t : threads){
			if(t.second.ip->getPos() == pos){
				std::cout << "\e[43;1m"; // Yellow background
				color = true;
				break;
			}
		}
		if(breakpoints.contains(pos)){
			std::cout << "\e[41;1m"; // Red background
			color = true;
		}
		if(watchpoints.contains(pos)){
			std::cout << "\e[34;1m"; // Blue text
			color = true;
		}
		if(pos == center){
			std::cout << "\e[4m"; // Underline
			color = true;
		}
		if(pos == ip.getPos()){
			std::cout << "\e[42;1m"; // Green background
			color = true;
		}
		std::cout << static_cast<char>(i);
		if(color){
			std::cout << "\e[0m";
		}
		pos.set(dim[0], pos[dim[0]]+1); // ++x
		if(pos[dim[0]] > end[dim[0]]){
			pos.set(dim[1], pos[dim[1]]+1); // ++y
			pos.set(dim[0], start[dim[0]]); // x = 0
			std::cout << std::endl;
		}
	}
}

}
