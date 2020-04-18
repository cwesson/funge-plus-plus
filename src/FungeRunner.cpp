/**
 * @file FungeRunner.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeRunner.h"
#include "FungeManager.h"

namespace Funge {

FungeRunner::FungeRunner(Field& f) :
	field(f),
	stack(),
	ip(f),
	thread(nullptr),
	normalState(*this, f, stack, ip),
	stringState(*this, stack),
	state(&normalState)
{
	run();
}

FungeRunner::FungeRunner(Field& f, const StackStack& s, const InstructionPointer& i) :
	field(f),
	stack(s),
	ip(i),
	thread(nullptr),
	normalState(*this, f, stack, ip),
	stringState(*this, stack),
	state(&normalState)
{
	ip.reverse();
	ip.next();
	run();
}

void FungeRunner::run(){
	FungeManager::getInstance()->addRunner(*this);
}

void FungeRunner::operator()(){
	while(!ip.isStopped()){
		bool done = false;
		while(!done && !ip.isStopped()){
			inst_t i = ip.get();
			done = state->execute(i);
			//std::cout << "\"" << i << "\"" << std::endl;
			if(!done && i != ' '){
				std::cerr << "Unimplemented instruction " << static_cast<int>(i) << " \'" << static_cast<char>(i) << "\' at " << ip << "." << std::endl;
				ip.reverse();
			}
			ip.next();
		}
		std::this_thread::yield();
	}
}

void FungeRunner::setState(FungeState& s){
	state = &s;
}

FungeState& FungeRunner::getNormalState(){
	return normalState;
}

FungeState& FungeRunner::getStringState(){
	return stringState;
}

}
