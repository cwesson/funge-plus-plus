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
	normalState(*this),
	stringState(*this),
	state(&normalState)
{
}

FungeRunner::FungeRunner(const FungeRunner& runner) :
	universe(runner.universe),
	field(runner.field),
	stack(runner.stack),
	ip(runner.ip),
	normalState(runner.normalState, *this),
	stringState(*this),
	state(&normalState)
{
	ip.reflect();
	ip.next();
}

FungeRunner::~FungeRunner(){
	ip.stop();
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
		done = execute(i);
		if(!done && i != ' '){
			std::cerr << "Unimplemented instruction " << static_cast<int>(i) << " \'" << static_cast<char>(i) << "\' at " << ip << "." << std::endl;
			ip.reflect();
		}
		ip.next();
	}
}

bool FungeRunner::execute(inst_t i){
	return state->execute(i);
}

void FungeRunner::setState(FungeState& s){
	state = &s;
}

FungeState& FungeRunner::getNormalState(){
	return normalState;
}

FungeState& FungeRunner::getStringState(inst_t i){
	stringState.setEnd(i);
	return stringState;
}

FungeUniverse& FungeRunner::getUniverse(){
	return universe;
}

Field& FungeRunner::getField(){
	return field;
}

StackStack& FungeRunner::getStack(){
	return stack;
}

InstructionPointer& FungeRunner::getIP(){
	return ip;
}

void FungeRunner::pushSemantic(inst_t i, semantic_t func){
	normalState.pushSemantic(i, func);
}

semantic_t FungeRunner::popSemantic(inst_t i){
	return normalState.popSemantic(i);
}

semantic_t FungeRunner::getSemantic(inst_t i){
	return normalState.getSemantic(i);
}

}
