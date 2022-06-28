/**
 * @file FungeRunner.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeRunner.h"
#include "FungeUniverse.h"
#include "FungeDebugger.h"

namespace Funge {

size_t FungeRunner::count = 0;

FungeRunner::FungeRunner(FungeUniverse& uni, const Vector& pos, const Vector& delta) :
	id(count++),
	universe(&uni),
	stack(new StackStack(*this)),
	ip(*this),
	parent(nullptr),
	normalState(*this),
	stringState(*this),
	state(&normalState)
{
	ip.setPos(pos);
	ip.setDelta(delta);
}

FungeRunner::FungeRunner(FungeUniverse& uni, const Vector& pos, const Vector& delta, FungeRunner& r) :
	id(count++),
	universe(&uni),
	stack(r.stack),
	ip(*this),
	parent(&r),
	normalState(*this),
	stringState(*this),
	state(&normalState)
{
	stack->setRunner(*this);
	ip.setPos(pos);
	ip.setDelta(delta);
}

FungeRunner::FungeRunner(const FungeRunner& runner) :
	id(count++),
	universe(runner.universe),
	stack(new StackStack(*runner.stack, *this)),
	ip(runner.ip, *this),
	parent(&runner),
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
	FungeError err = ERROR_UNSPEC;
	do {
		getUniverse().getDebugger().tick(*this);
		inst_t i = ip.get();
		err = execute(i);
		switch(err){
			[[likely]] case ERROR_NONE:
			[[likely]] case ERROR_SKIP:
				ip.next();
				break;
			case ERROR_BLOCK:
				break;
			case ERROR_UNIMP:
				std::cerr << "Unimplemented instruction " << static_cast<int>(i) << " \'" << static_cast<char>(i) << "\' at " << ip << "." << std::endl;
				[[fallthrough]];
			case ERROR_NOTAVAIL:
			case ERROR_UNSPEC:
			[[unlikely]] default:
				getUniverse().getDebugger().trap(*this);
				ip.reflect();
				ip.next();
				break;
		}
	} while(err == ERROR_SKIP);
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

FungeState& FungeRunner::getStringState(inst_t i){
	stringState.setEnd(i);
	return stringState;
}

size_t FungeRunner::getID() const{
	return id;
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

const FungeRunner* FungeRunner::getParent(){
	return parent;
}

}
