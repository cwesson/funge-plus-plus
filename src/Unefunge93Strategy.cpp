/**
 * @file Unefunge93Strategy.cpp
 * Strategy for Unefunge-93 commands.
 * @author Conlan Wesson
 */

#include "Unefunge93Strategy.h"
#include "FungeRunner.h"
#include "FungeUtilities.h"
#include "FungeUniverse.h"
#include "ScopedTermios.h"
#include <iostream>

namespace Funge {


Unefunge93Strategy::Unefunge93Strategy(FungeRunner& r) :
	FungeStrategy(r)
{
	r.pushSemantic(' ', std::bind(&Unefunge93Strategy::instructionSkip, this));
	r.pushSemantic('\t', std::bind(&Unefunge93Strategy::instructionSkip, this));
	r.pushSemantic('0', std::bind(&Unefunge93Strategy::instructionPush, this, 0));
	r.pushSemantic('1', std::bind(&Unefunge93Strategy::instructionPush, this, 1));
	r.pushSemantic('2', std::bind(&Unefunge93Strategy::instructionPush, this, 2));
	r.pushSemantic('3', std::bind(&Unefunge93Strategy::instructionPush, this, 3));
	r.pushSemantic('4', std::bind(&Unefunge93Strategy::instructionPush, this, 4));
	r.pushSemantic('5', std::bind(&Unefunge93Strategy::instructionPush, this, 5));
	r.pushSemantic('6', std::bind(&Unefunge93Strategy::instructionPush, this, 6));
	r.pushSemantic('7', std::bind(&Unefunge93Strategy::instructionPush, this, 7));
	r.pushSemantic('8', std::bind(&Unefunge93Strategy::instructionPush, this, 8));
	r.pushSemantic('9', std::bind(&Unefunge93Strategy::instructionPush, this, 9));
	// Flow Control
	r.pushSemantic('<', std::bind(&Unefunge93Strategy::instructionWest, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('>', std::bind(&Unefunge93Strategy::instructionEast, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('@', std::bind(&Unefunge93Strategy::instructionStop, this));
	r.pushSemantic('#', std::bind(&Unefunge93Strategy::instructionTrampoline, this));
	r.pushSemantic('_', std::bind(&Unefunge93Strategy::instructionIf, this));
	r.pushSemantic('?', std::bind(&Unefunge93Strategy::instructionGoAway, this));
	// Arithmetic Operators
	r.pushSemantic('!', std::bind(&Unefunge93Strategy::instructionNot, this));
	r.pushSemantic('%', std::bind(&Unefunge93Strategy::instructionRemainder, this));
	r.pushSemantic('*', std::bind(&Unefunge93Strategy::instructionMultiply, this));
	r.pushSemantic('+', std::bind(&Unefunge93Strategy::instructionAdd, this));
	r.pushSemantic('-', std::bind(&Unefunge93Strategy::instructionSubtract, this));
	r.pushSemantic('/', std::bind(&Unefunge93Strategy::instructionDivide, this));
	r.pushSemantic('`', std::bind(&Unefunge93Strategy::instructionGreater, this));
	// Stack Operators
	r.pushSemantic('$', std::bind(&Unefunge93Strategy::instructionPop, this));
	r.pushSemantic(':', std::bind(&Unefunge93Strategy::instructionDuplicate, this));
	r.pushSemantic('\\', std::bind(&Unefunge93Strategy::instructionSwap, this));
	// Input
	r.pushSemantic('&', std::bind(&Unefunge93Strategy::instructionNumIn, this));
	r.pushSemantic('~', std::bind(&Unefunge93Strategy::instructionCharIn, this));
	r.pushSemantic('\"', std::bind(&Unefunge93Strategy::instructionString, this));
	// Output
	r.pushSemantic('.', std::bind(&Unefunge93Strategy::instructionNumOut, this));
	r.pushSemantic(',', std::bind(&Unefunge93Strategy::instructionCharOut, this));
	// Self-Modifying
	r.pushSemantic('g', std::bind(&Unefunge93Strategy::instructionGet, this));
	r.pushSemantic('p', std::bind(&Unefunge93Strategy::instructionPut, this));

	r.setErrorHandler(std::bind(&Unefunge93Strategy::errorHandler, this, std::placeholders::_1));
}

FungeError Unefunge93Strategy::instructionSkip(){
	return ERROR_SKIP;
}

FungeError Unefunge93Strategy::instructionPush(int n){
	stack.top().push(n);
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionWest(){
	ip.setDelta(Vector{-1});
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionEast(){
	ip.setDelta(Vector{1});
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionStop(){
	ip.stop();
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionTrampoline(){
	ip.next();
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionIf(){
	if(stack.top().pop() == 0){
		ip.setDelta(Vector{1});
	}else{
		ip.setDelta(Vector{-1});
	}
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionGoAway(){
	size_t d = runner.getUniverse().dimensions()*2;
	int r = random(0, d-1);
	Vector v;
	if(r & 1){
		v.set(r>>1, -1);
	}else{
		v.set(r>>1, 1);
	}
	ip.setDelta(v);
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionNot(){
	stack.top().push(!stack.top().pop());
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionRemainder(){
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	if(a == 0){
		stack.top().push(0);
	}else{
		stack.top().push(b%a);
	}
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionMultiply(){
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	stack.top().push(b*a);
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionAdd(){
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	stack.top().push(b+a);
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionSubtract(){
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	stack.top().push(b-a);
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionDivide(){
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	if(a == 0){
		stack.top().push(0);
	}else{
		stack.top().push(b/a);
	}
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionGreater(){
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	if(b > a){
		stack.top().push(1);
	}else{
		stack.top().push(0);
	}
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionPop(){
	stack.top().pop();
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionDuplicate(){
	stack_t x = stack.top().pop();
	stack.top().push(x);
	stack.top().push(x);
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionSwap(){
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	stack.top().push(a);
	stack.top().push(b);
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionNumIn(){
	ScopedTermios term(~(ICANON));
	stack_t num = 0;
	int c = getchar();
	if(c == EOF){
		return ERROR_UNSPEC;
	}
	while(c < '0' || c > '9'){
		c = getchar();
		if(c == EOF){
			return ERROR_UNSPEC;
		}
	}
	while(c >= '0' && c <= '9'){
		num = (num*10) + (c-'0');
		c = getchar();
		if(c == EOF){
			return ERROR_UNSPEC;
		}
	}
	ungetc(c, stdin);
	stack.top().push(num);
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionCharIn(){
	ScopedTermios term(~(ICANON));
	int q = getchar();
	if(q == EOF){
		return ERROR_UNSPEC;
	}
	if(q == 13){
		q = getchar();
		if(q == EOF){
			return ERROR_UNSPEC;
		}
	}
	stack.top().push(q);
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionString(){
	runner.setState(runner.getStringState());
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionCharOut(){
	stack_t x = stack.top().pop();
	if(x == 10){
		std::cout << std::endl;
	}else{
		std::cout << static_cast<char>(x);
	}
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionNumOut(){
	stack_t x = stack.top().pop();
	std::cout << static_cast<int>(x) << ' ';
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionGet(){
	const Vector& storage = ip.getStorage();
	Vector v = popVector(runner);
	stack.top().push(static_cast<stack_t>(field.get(v+storage)));
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::instructionPut(){
	const Vector& storage = ip.getStorage();
	Vector v = popVector(runner);
	field.put(v+storage, stack.top().pop());
	return ERROR_NONE;
}

FungeError Unefunge93Strategy::errorHandler(FungeError e){
	inst_t i = ip.get();
	switch(e){
		[[unlikely]] case ERROR_NONE:
		[[unlikely]] case ERROR_SKIP:
		[[unlikely]] case ERROR_BLOCK:
			break;
		case ERROR_UNIMP:
			std::cerr << "Unimplemented instruction " << static_cast<int>(i) << " \'" << static_cast<char>(i) << "\' at " << ip << "." << std::endl;
			[[fallthrough]];
		case ERROR_NOTAVAIL:
		case ERROR_UNSPEC:
		[[unlikely]] default:
			ip.reflect();
			ip.next();
			break;
	}
	return e;
}

FungeStrategy* Unefunge93Strategy::clone(FungeRunner& r) const{
	return new Unefunge93Strategy(r);
}

}
