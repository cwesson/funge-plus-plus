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
			.state = STATE_START,
		}});
		std::cout << "New IP " << id << std::endl;
	}
	
	auto bp = breakpoints.find(ip.getPos());
	if(bp != breakpoints.end()){
		std::cout << "Breakpoint " << ip.getPos() << std::endl;
		threads[id].state = STATE_BREAK;
	}
	
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
		std::cout << "(defunge) " << std::flush;
		
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
			break;
		}else if(cmd == "peek" || cmd == "p"){
			size_t c = 0;
			iss >> c;
			if(c == 0){
				for(size_t i = 0; i < threads[tid].stack->top().size(); ++i){
					std::cout << threads[tid].stack->top().get(i+1) << " " << std::endl;
				}
			}else{
				std::cout << threads[tid].stack->top().get(c) << std::endl;
			}
		}else if(cmd == "get" || cmd == "g"){
			std::cout << field.get(threads[tid].ip->getPos()) << std::endl;
		}else if(cmd == "list" || cmd == "l"){
			printField(field, threads[tid].ip->getPos(), Vector{3,3});
		}else if(cmd == "break" || cmd == "b"){
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
			iss >> tid;
			printIP(*threads[tid].ip);
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
		if(pos == center){
			std::cout << "\e[42;1m";
		}
		std::cout << static_cast<char>(i);
		if(pos == center){
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
