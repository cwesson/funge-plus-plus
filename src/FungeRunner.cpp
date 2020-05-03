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
	normalState(*this, f, stack, ip),
	stringState(*this, stack, ip),
	state(&normalState)
{
	run();
}

FungeRunner::FungeRunner(Field& f, const StackStack& s, const InstructionPointer& i) :
	field(f),
	stack(s),
	ip(i),
	normalState(*this, f, stack, ip),
	stringState(*this, stack, ip),
	state(&normalState)
{
	ip.reverse();
	ip.next();
	run();
}

void FungeRunner::run(){
	FungeManager::getInstance()->addRunner(this);
}

bool FungeRunner::isRunning() const{
	return !ip.isStopped();
}

void FungeRunner::operator()(){
	while(!ip.isStopped()){
		tick();
		std::this_thread::yield();
	}
}

void FungeRunner::tick(){
	bool done = false;
	while(!done && !ip.isStopped()){
		inst_t i = ip.get();
		//std::cout << ip.getPos() << "\"" << static_cast<char>(i) << "\"" << std::endl;
		done = state->execute(i);
		if(!done && i != ' '){
			std::cerr << "Unimplemented instruction " << static_cast<int>(i) << " \'" << static_cast<char>(i) << "\' at " << ip << "." << std::endl;
			ip.reverse();
		}
		ip.next();
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
