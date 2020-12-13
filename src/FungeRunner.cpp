/**
 * @file FungeRunner.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeRunner.h"
#include "FungeDebugger.h"

namespace Funge {

FungeRunner::FungeRunner(FungeUniverse& uni) :
	universe(uni),
	field(uni.getField()),
	stack(),
	ip(uni.getField()),
	normalState(*this, uni.getField(), stack, ip),
	stringState(*this, stack, ip),
	state(&normalState)
{
}

FungeRunner::FungeRunner(FungeUniverse& uni, const FungeRunner& runner) :
	universe(uni),
	field(runner.field),
	stack(runner.stack),
	ip(runner.ip),
	normalState(*this, universe.getField(), stack, ip),
	stringState(*this, stack, ip),
	state(&normalState)
{
	ip.reverse();
	ip.next();
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
		FungeDebugger::tick(field, stack, ip);
		inst_t i = ip.get();
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

FungeUniverse& FungeRunner::getUniverse(){
	return universe;
}

}
