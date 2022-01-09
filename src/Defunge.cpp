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
	mutex(),
	debugger(nullptr),
	runner(nullptr),
	cmdMap()
{
	cmdMap["run"]       = &Defunge::runCommand;
	cmdMap["continue"]  = &Defunge::runCommand;
	cmdMap["con"]       = &Defunge::runCommand;
	cmdMap["c"]         = &Defunge::runCommand;

	cmdMap["quit"]      = &Defunge::quitCommand;
	cmdMap["q"]         = &Defunge::quitCommand;

	cmdMap["step"]      = &Defunge::stepCommand;
	cmdMap["stp"]       = &Defunge::stepCommand;
	cmdMap["s"]         = &Defunge::stepCommand;

	cmdMap["peek"]      = &Defunge::peekCommand;
	cmdMap["p"]         = &Defunge::peekCommand;

	cmdMap["delta"]     = &Defunge::deltaCommand;
	cmdMap["dir"]       = &Defunge::deltaCommand;
	cmdMap["d"]         = &Defunge::deltaCommand;

	cmdMap["storage"]   = &Defunge::storageCommand;

	cmdMap["position"]  = &Defunge::positionCommand;
	cmdMap["pos"]       = &Defunge::positionCommand;

	cmdMap["thread"]    = &Defunge::threadCommand;
	cmdMap["t"]         = &Defunge::threadCommand;

	cmdMap["backtrace"] = &Defunge::backtraceCommand;
	cmdMap["bt"]        = &Defunge::backtraceCommand;

	cmdMap["setdelta"]  = &Defunge::setdeltaCommand;
	cmdMap["setpos"]    = &Defunge::setposCommand;

	cmdMap["get"]       = &Defunge::getCommand;
	cmdMap["g"]         = &Defunge::getCommand;

	cmdMap["list"]      = &Defunge::listCommand;
	cmdMap["l"]         = &Defunge::listCommand;

	cmdMap["break"]     = &Defunge::breakCommand;
	cmdMap["bp"]        = &Defunge::breakCommand;

	cmdMap["watch"]     = &Defunge::watchCommand;
	cmdMap["wp"]        = &Defunge::watchCommand;

	cmdMap["read"]      = &Defunge::readCommand;

	cmdMap["universe"]  = &Defunge::universeCommand;
	cmdMap["u"]         = &Defunge::universeCommand;
}

void Defunge::debug(FungeDebugger* dbg, FungeRunner* run){
	std::lock_guard<std::recursive_mutex> guard(mutex);
	debugger = dbg;
	runner = run;
	const InstructionPointer& ip = runner->getIP();

	size_t id = ip.getID();
	auto found = dbg->threads.find(id);
	if(found == dbg->threads.end()){
		dbg->threads.insert({id, {
			.runner = run,
			.backtrace = {},
			.state = FungeDebugger::STATE_START,
		}});
		dbg->intro(*runner);
		std::cout << "New IP " << id << std::endl;
	}
	dbg->lastThread = id;
	
	if(dbg->breakpoints.contains(ip.getPos())){
		dbg->intro(*runner);
		std::cout << "Breakpoint " << ip.getPos() << std::endl;
		dbg->threads[id].state = FungeDebugger::STATE_BREAK;
	}
	
	if(dbg->threads[id].backtrace.size() >= FungeDebugger::MAX_BACKTRACE){
		dbg->threads[id].backtrace.pop_back();
	}
	dbg->threads[id].backtrace.push_front(ip.getPos());
	
	switch(dbg->threads[id].state){
		case FungeDebugger::STATE_RUN:
			return;
		case FungeDebugger::STATE_START:
		case FungeDebugger::STATE_STEP:
		case FungeDebugger::STATE_BREAK:
			break;
	}
	
	printIP(ip);
	
	for(bool debugging = true; debugging; ){
		std::cout << "\e[33m(defunge)\e[0m " << std::flush;
		
		std::string line;
		std::getline(std::cin, line);
		auto iss = std::istringstream(line);
		
		std::string cmd;
		iss >> cmd;
		
		if(cmdMap.contains(cmd)){
			debugger_command_t func = cmdMap[cmd];
			Error err = (this->*func)(iss);
			switch(err){
				case DEFUNGE_OK:
					break;
				case DEFUNGE_BREAK:
					debugging = false;
					break;
				case DEFUNGE_NO_THREAD:
					std::cout << "No thread." << std::endl;
					break;
				default:
					std::cout << "Error" << std::endl;
					break;
			}
		}
	}
}

void Defunge::printIP(const InstructionPointer& ip){
	std::cout << ip.getID() << ": " << ip.getPos() << " \"" << static_cast<char>(ip.get()) << "\"" << std::endl;
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
		if(ip != nullptr && pos == ip->getPos()){
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

Defunge::Error Defunge::runCommand(std::istringstream& iss){
	(void)iss;
	if(runner == nullptr || debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	size_t tid = runner->getIP().getID();
	debugger->threads[tid].state = FungeDebugger::STATE_RUN;
	return DEFUNGE_BREAK;
}

Defunge::Error Defunge::quitCommand(std::istringstream& iss){
	(void)iss;

	FungeMultiverse::getInstance().killAll(1);
	return DEFUNGE_BREAK;
}

Defunge::Error Defunge::stepCommand(std::istringstream& iss){
	(void)iss;
	if(runner == nullptr || debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	size_t tid = runner->getIP().getID();
	debugger->threads[tid].state = FungeDebugger::STATE_STEP;
	return DEFUNGE_BREAK;
}

Defunge::Error Defunge::peekCommand(std::istringstream& iss){
	(void)iss;
	if(runner == nullptr || debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

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
	return DEFUNGE_OK;
}

Defunge::Error Defunge::deltaCommand(std::istringstream& iss){
	(void)iss;
	if(runner == nullptr || debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	std::cout << "Delta " << runner->getIP().getDelta() << std::endl;
	return DEFUNGE_OK;
}

Defunge::Error Defunge::storageCommand(std::istringstream& iss){
	(void)iss;
	if(runner == nullptr || debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	std::cout << "Storage " << runner->getIP().getStorage() << std::endl;
	return DEFUNGE_OK;
}

Defunge::Error Defunge::positionCommand(std::istringstream& iss){
	(void)iss;
	if(runner == nullptr || debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	printIP(runner->getIP());
	return DEFUNGE_OK;
}

Defunge::Error Defunge::threadCommand(std::istringstream& iss){
	if(debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	size_t tid = 0;
	if(runner != nullptr){
		tid = runner->getIP().getID();
	}
	size_t thread = tid;
	iss >> thread;
	if(debugger->threads.contains(thread)){
		tid = thread;
		runner = debugger->threads[tid].runner;
	}
	for(auto t : debugger->threads){
		if(runner != nullptr && t.second.runner->getIP().getID() == tid){
			std::cout << "* ";
		}else{
			std::cout << "  ";
		}
		printIP(t.second.runner->getIP());
	}
	return DEFUNGE_OK;
}

Defunge::Error Defunge::backtraceCommand(std::istringstream& iss){
	(void)iss;
	if(runner == nullptr || debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	std::cout << "Backtrace" << std::endl;
	size_t i = 0;
	size_t tid = runner->getIP().getID();
	const Field& field = runner->getUniverse().getField();
	for(auto b : debugger->threads[tid].backtrace){
		std::cout << "#" << i++ << "  " << b << " \"" << static_cast<char>(field.get(b)) << "\"" << std::endl;
	}
	return DEFUNGE_OK;
}

Defunge::Error Defunge::setdeltaCommand(std::istringstream& iss){
	if(runner == nullptr || debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	Vector v;
	iss >> v;
	InstructionPointer& ip = runner->getIP();
	ip.setDelta(v);
	std::cout << "Delta " << ip.getDelta() << std::endl;
	return DEFUNGE_OK;
}

Defunge::Error Defunge::setposCommand(std::istringstream& iss){
	if(runner == nullptr || debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	Vector v;
	iss >> v;
	InstructionPointer& ip = runner->getIP();
	ip.setPos(v);
	printIP(ip);
	return DEFUNGE_OK;
}

Defunge::Error Defunge::getCommand(std::istringstream& iss){
	if(debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	const InstructionPointer* ip = nullptr;
	if(runner != nullptr){
		ip = &runner->getIP();
	}
	Vector v;
	iss >> v;
	if(runner != nullptr && v.size() == 0){
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
	
	const Field& field = debugger->universe.getField();
	printField(debugger, field, v, s, d, ip);
	return DEFUNGE_OK;
}

Defunge::Error Defunge::listCommand(std::istringstream& iss){
	if(runner == nullptr || debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	const InstructionPointer& ip = runner->getIP();
	const Field& field = runner->getField();

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
	printField(debugger, field, ip.getPos(), s, d, &ip);
	return DEFUNGE_OK;
}

Defunge::Error Defunge::breakCommand(std::istringstream& iss){
	if(debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	Vector v;
	iss >> v;
	debugger->addBreakpoint(v);
	for(auto b : debugger->breakpoints){
		std::cout << "Breakpoint " << b << std::endl;
	}
	return DEFUNGE_OK;
}

Defunge::Error Defunge::watchCommand(std::istringstream& iss){
	if(debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	Vector v;
	iss >> v;
	debugger->addWatchpoint(v);
	for(auto w : debugger->watchpoints){
		std::cout << "Watchpoint " << w << std::endl;
	}
	return DEFUNGE_OK;
}

Defunge::Error Defunge::readCommand(std::istringstream& iss){
	if(debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	const Field& field = debugger->universe.getField();
	Vector v;
	iss >> v;
	inst_t i = field.get(v);
	std::cout << "Value = (" << i << ") \"" << static_cast<char>(i) << "\"" << std::endl;
	return DEFUNGE_OK;
}

Defunge::Error Defunge::universeCommand(std::istringstream& iss){
	if(debugger == nullptr){
		return DEFUNGE_NO_THREAD;
	}

	FungeMultiverse& multi = FungeMultiverse::getInstance();

	std::string name;
	iss >> name;
	if(name != ""){
		FungeUniverse* uni = multi[name];
		if(uni != nullptr){
			debugger = &uni->getDebugger();
			if(debugger->threads.empty()){
				runner = nullptr;
			}else{
				size_t id = debugger->lastThread;
				runner = debugger->threads[id].runner;
			}
		}
	}

	std::string current = debugger->universe.getName();
	for(auto uni = multi.cbegin(); uni != multi.cend(); ++uni){
		if(current == uni->first){
			std::cout << "* ";
		}else{
			std::cout << "  ";
		}
		std::cout << uni->first << std::endl;
	}
	return DEFUNGE_OK;
}

}
