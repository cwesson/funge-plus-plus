/**
 * @file FungeRunner.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeRunner.h"
#include "FungeUniverse.h"
#include "FungeDebugger.h"

namespace Funge {

FungeRunner::FungeRunner(FungeUniverse& uni, const Vector& pos, const Vector& delta) :
	universe(&uni),
	stack(new StackStack(*this)),
	ip(*this),
	normalState(*this),
	stringState(*this),
	state(&normalState)
{
	ip.setPos(pos);
	ip.setDelta(delta);
}

FungeRunner::FungeRunner(FungeUniverse& uni, const Vector& pos, const Vector& delta, FungeRunner& r) :
	universe(&uni),
	stack(r.stack),
	ip(*this),
	normalState(*this),
	stringState(*this),
	state(&normalState)
{
	stack->setRunner(*this);
	ip.setPos(pos);
	ip.setDelta(delta);
}

FungeRunner::FungeRunner(const FungeRunner& runner) :
	universe(runner.universe),
	stack(new StackStack(*runner.stack, *this)),
	ip(runner.ip, *this),
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

bool FungeRunner::isRunning() const {
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
		getUniverse().getDebugger().tick(*this);
		inst_t i = ip.get();
		FungeError err = execute(i);
		switch(err){
			case ERROR_NONE:
				ip.next();
				done = true;
				break;
			case ERROR_SKIP:
				ip.next();
				done = false;
				break;
			case ERROR_BLOCK:
				done = true;
				break;
			case ERROR_UNIMP:
				std::cerr << "Unimplemented instruction " << static_cast<int>(i) << " \'" << static_cast<char>(i) << "\' at " << ip << "." << std::endl;
				ip.reflect();
				ip.next();
				break;
			case ERROR_UNSPEC:
			default:
				ip.reflect();
				ip.next();
				break;
		}
	}
}

FungeError FungeRunner::execute(inst_t i){
	return state->execute(i);
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
	return *universe;
}

Field& FungeRunner::getField(){
	return universe->getField();
}

StackStack& FungeRunner::getStack(){
	return *stack;
}

InstructionPointer& FungeRunner::getIP(){
	return ip;
}

const InstructionPointer& FungeRunner::getIP() const{
	return ip;
}

bool FungeRunner::isMode(FungeMode m) const {
	return universe->isMode(m);
}

stack_t FungeRunner::getMode() const {
	return universe->getMode();
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

void FungeRunner::setUniverse(FungeUniverse& other){
	universe = &other;
}

}
