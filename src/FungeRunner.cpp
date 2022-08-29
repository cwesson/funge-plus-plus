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
	stack(new StackStack()),
	ip(*this),
	parent(nullptr),
	errorHandler(nullptr),
	normalState(*this),
	stringState(*this),
	state(&normalState)
{
	ip.setPos(pos);
	ip.setDelta(delta);
	stack->setMode(getMode());
}

FungeRunner::FungeRunner(FungeUniverse& uni, const Vector& pos, const Vector& delta, FungeRunner& r) :
	id(count++),
	universe(&uni),
	stack(r.stack),
	ip(*this),
	parent(&r),
	errorHandler(nullptr),
	normalState(*this),
	stringState(*this),
	state(&normalState)
{
	ip.setPos(pos);
	ip.setDelta(delta);
	stack->setMode(getMode());
}

FungeRunner::FungeRunner(const FungeRunner& runner) :
	id(count++),
	universe(runner.universe),
	stack(new StackStack(*runner.stack)),
	ip(runner.ip, *this),
	parent(&runner),
	errorHandler(runner.errorHandler),
	normalState(runner.normalState, *this),
	stringState(*this),
	state(&normalState)
{
	ip.reflect();
	ip.next();
	stack->setMode(getMode());
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
				break;
			case ERROR_BLOCK:
				break;
			case ERROR_UNIMP:
			case ERROR_NOTAVAIL:
			case ERROR_UNSPEC:
			[[unlikely]] default:
				getUniverse().getDebugger().trap(*this);
				if(errorHandler != nullptr){
					err = errorHandler(err);
				}else{
					ip.next();
				}
				break;
		}
		if(err == ERROR_NONE || err == ERROR_SKIP){
			ip.next();
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

void FungeRunner::setMode(FungeMode m){
	stack->setMode(m);
}

FungeMode FungeRunner::getMode() const {
	return universe->getMode();
}

void FungeRunner::pushSemantic(inst_t i, FungeSemantic* func){
	normalState.pushSemantic(i, func);
}

void FungeRunner::pushSemantic(inst_t i, std::function<FungeError()> func, FungeSemantic::SemanticFlags flg){
	normalState.pushSemantic(i, new FungeSemantic(func, flg));
}

FungeSemantic* FungeRunner::popSemantic(inst_t i){
	return normalState.popSemantic(i);
}

FungeSemantic* FungeRunner::getSemantic(inst_t i){
	return normalState.getSemantic(i);
}

void FungeRunner::setErrorHandler(std::function<FungeError(FungeError)> func){
	errorHandler = func;
}

void FungeRunner::setUniverse(FungeUniverse& other){
	universe = &other;
}

const FungeRunner* FungeRunner::getParent(){
	return parent;
}

}
