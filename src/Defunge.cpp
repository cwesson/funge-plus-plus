/**
 * @file Defunge.cpp
 * Funge Debugger.
 * @author Conlan Wesson
 */

#include "Defunge.h"
#include "FungeMultiverse.h"
#include <mutex>
#include <iostream>
#include <sstream>

namespace Funge {

Defunge& Defunge::getInstance(){
	static Defunge instance;

	return instance;
}

Defunge::Defunge():
	mutex()
{

}

void Defunge::debug(FungeDebugger* dbg, FungeRunner* runner){
	InstructionPointer* ip = &runner->getIP();

	std::lock_guard<std::recursive_mutex> guard(mutex);
	size_t id = ip->getID();
	auto found = dbg->threads.find(id);
	if(found == dbg->threads.end()){
		dbg->threads.insert({id, {
			.runner = runner,
			.backtrace = {},
			.state = FungeDebugger::STATE_START,
		}});
		dbg->intro(*runner);
		std::cout << "New IP " << id << std::endl;
	}
	dbg->lastThread = id;
	
	if(dbg->breakpoints.contains(ip->getPos())){
		dbg->intro(*runner);
		std::cout << "Breakpoint " << ip->getPos() << std::endl;
		dbg->threads[id].state = FungeDebugger::STATE_BREAK;
	}
	
	if(dbg->threads[id].backtrace.size() >= FungeDebugger::MAX_BACKTRACE){
		dbg->threads[id].backtrace.pop_back();
	}
	dbg->threads[id].backtrace.push_front(ip->getPos());
	
	switch(dbg->threads[id].state){
		case FungeDebugger::STATE_RUN:
			return;
		case FungeDebugger::STATE_START:
		case FungeDebugger::STATE_STEP:
		case FungeDebugger::STATE_BREAK:
			break;
	}
	
	printIP(ip);
	
	while(dbg->threads[id].state != FungeDebugger::STATE_RUN && runner->isRunning()){
		const Field& field = runner->getField();
		ip = &runner->getIP();
		size_t tid = ip->getID();

		std::cout << "\e[33m(defunge)\e[0m " << std::flush;
		
		std::string line;
		std::getline(std::cin, line);
		auto iss = std::istringstream(line);
		
		std::string cmd;
		iss >> cmd;
		
		if(cmd == "run" || cmd == "continue" || cmd == "con" || cmd == "c"){
			dbg->threads[tid].state = FungeDebugger::STATE_RUN;
		}else if(cmd == "quit" || cmd == "q"){
			FungeMultiverse::getInstance().killAll(1);
			return;
		}else if(cmd == "step" || cmd == "stp" || cmd == "s"){
			dbg->threads[tid].state = FungeDebugger::STATE_STEP;
			break;
		}else if(cmd == "peek" || cmd == "p"){
			const StackStack* stack = &runner->getStack();
			size_t c = 0;
			iss >> c;
			if(c == 0){
				for(size_t j = 0; j < stack->size(); ++j){
					std::cout << "[0] ";
					for(size_t i = stack->at(j).size(); i > 0; --i){
						std::cout << stack->at(j).get(i) << " ";
					}
					std::cout << std::endl;
				}
			}else{
				size_t s = 0;
				iss >> s;
				std::cout << stack->at(s).get(c) << std::endl;
			}
		}else if(cmd == "get" || cmd == "g"){
			Vector v;
			iss >> v;
			if(v.size() == 0){
				v = ip->getPos();
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
			printField(dbg, field, v, s, d, ip);
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
			printField(dbg, field, ip->getPos(), s, d, ip);
		}else if(cmd == "break" || cmd == "bp"){
			Vector v;
			iss >> v;
			dbg->addBreakpoint(v);
			for(auto b : dbg->breakpoints){
				std::cout << "Breakpoint " << b << std::endl;
			}
		}else if(cmd == "watch" || cmd == "wp"){
			Vector v;
			iss >> v;
			dbg->addWatchpoint(v);
			for(auto w : dbg->watchpoints){
				std::cout << "Watchpoint " << w << std::endl;
			}
		}else if(cmd =="delta" || cmd == "dir" || cmd == "d"){
			std::cout << "Delta " << ip->getDelta() << std::endl;
		}else if(cmd == "storage"){
			std::cout << "Storage " << ip->getStorage() << std::endl;
		}else if(cmd == "position" || cmd == "pos"){
			printIP(ip);
		}else if(cmd == "thread" || cmd == "t"){
			size_t thread = tid;
			iss >> thread;
			if(thread != tid && dbg->threads.contains(thread)){
				tid = thread;
				runner = dbg->threads[tid].runner;
				printIP(ip);
			}
			for(auto t : dbg->threads){
				if(t.second.runner->getIP().getID() == tid){
					std::cout << "* ";
				}else{
					std::cout << "  ";
				}
				printIP(&t.second.runner->getIP());
			}
		}else if(cmd == "backtrace" || cmd == "bt"){
			std::cout << "Backtrace" << std::endl;
			size_t i = 0;
			for(auto b : dbg->threads[tid].backtrace){
				std::cout << "#" << i++ << "  " << b << " \"" << static_cast<char>(field.get(b)) << "\"" << std::endl;
			}
		}else if(cmd == "setdelta"){
			Vector v;
			iss >> v;
			ip->setDelta(v);
			std::cout << "Delta " << ip->getDelta() << std::endl;
		}else if(cmd == "setpos"){
			Vector v;
			iss >> v;
			ip->setPos(v);
			printIP(ip);
		}else if(cmd == "read"){
			Vector v;
			iss >> v;
			inst_t i = field.get(v);
			std::cout << "Value = (" << i << ") \"" << static_cast<char>(i) << "\"" << std::endl;
		}else if(cmd == "universe" || cmd == "u"){
			FungeMultiverse& multi = FungeMultiverse::getInstance();

			std::string name;
			iss >> name;
			if(name != ""){
				FungeUniverse* uni = multi[name];
				if(uni != nullptr){
					dbg = &uni->getDebugger();
					id = dbg->lastThread;
					runner = dbg->threads[id].runner;
				}
			}

			std::string current = runner->getUniverse().getName();
			for(auto uni = multi.cbegin(); uni != multi.cend(); ++uni){
				if(current == uni->first){
					std::cout << "* ";
				}else{
					std::cout << "  ";
				}
				std::cout << uni->first << std::endl;
			}
		}
		
	}
}

void Defunge::printIP(const InstructionPointer* ip){
	std::cout << ip->getID() << ": " << ip->getPos() << " \"" << static_cast<char>(ip->get()) << "\"" << std::endl;
}

void Defunge::printField(FungeDebugger* dbg, const Field& field, const Vector& center, const Vector& size, const Vector& dim, const InstructionPointer* ip){
	const Vector start = center-size;
	const Vector end = center+size;
	Vector pos = start;
	while(pos <= end){
		inst_t i = field.get(pos);
		bool color = false;
		for(auto t : dbg->threads){
			if(t.second.runner->getIP().getPos() == pos){
				std::cout << "\e[43;1m"; // Yellow background
				color = true;
				break;
			}
		}
		if(dbg->breakpoints.contains(pos)){
			std::cout << "\e[41;1m"; // Red background
			color = true;
		}
		if(dbg->watchpoints.contains(pos)){
			std::cout << "\e[34;1m"; // Blue text
			color = true;
		}
		if(pos == center){
			std::cout << "\e[4m"; // Underline
			color = true;
		}
		if(pos == ip->getPos()){
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
