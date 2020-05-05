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
	mutex()
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

void FungeDebugger::tick(const Field& field, const StackStack& stack, const InstructionPointer& ip){
	if(funge_config.debug){
		FungeDebugger* inst = getInstance();
		inst->debug(field, stack, ip);
	}
}

void FungeDebugger::debug(const Field& field, const StackStack& stack, const InstructionPointer& ip){
	std::lock_guard<std::mutex> guard(mutex);
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
	
	auto bp = breakpoints.find(ip.getPos());
	if(bp != breakpoints.end()){
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
		
		if(cmd == "run"){
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
					for(size_t i = 0; i < threads[tid].stack->at(j).size(); ++i){
						std::cout << threads[tid].stack->at(j).get(i+1) << " ";
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
			printField(field, v, Vector{3,3});
		}else if(cmd == "list" || cmd == "l"){
			dim_t s = 0;
			iss >> s;
			if(s == 0){
				s = 3;
			}
			printField(field, threads[tid].ip->getPos(), Vector{std::abs(s),std::abs(s)});
		}else if(cmd == "break" || cmd == "bp"){
			Vector v;
			iss >> v;
			breakpoints.insert(v);
			for(auto b : breakpoints){
				std::cout << "Breakpoint " << b << std::endl;
			}
		}else if(cmd =="delta" || cmd == "dir" || cmd == "d"){
			std::cout << "Delta " << threads[tid].ip->getDelta() << std::endl;
		}else if(cmd == "storage"){
			std::cout << "Storage " << threads[tid].ip->getStorage() << std::endl;
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
		}
		
	}
}

void FungeDebugger::printIP(const InstructionPointer& ip){
	std::cout << ip.getID() << ": " << ip.getPos() << " \"" << static_cast<char>(ip.get()) << "\"" << std::endl;
}

void FungeDebugger::printField(const Field& field, const Vector& center, const Vector& size){
	const Vector start = center-size;
	const Vector end = center+size;
	Vector pos = start;
	while(pos != end){
		inst_t i = field.get(pos);
		bool color = false;
		for(auto t : threads){
			if(t.second.ip->getPos() == pos){
				std::cout << "\e[41;1m";
				color = true;
				break;
			}
		}
		if(pos == center){
			std::cout << "\e[42;1m";
			color = true;
		}
		std::cout << static_cast<char>(i);
		if(color){
			std::cout << "\e[0m";
		}
		pos.set(0, pos[0]+1); // ++x
		if(pos[0] > end[0]){
			pos.set(1, pos[1]+1); // ++y
			pos.set(0, start[0]); // x = 0
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

}
