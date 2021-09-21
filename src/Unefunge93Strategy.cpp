/**
 * @file Unefunge93Strategy.cpp
 * Strategy for Unefunge-93 commands.
 * @author Conlan Wesson
 */

#include "Unefunge93Strategy.h"
#include "FungeConfig.h"
#include "FungeRunner.h"
#include "FungeUtilities.h"
#include <iostream>

namespace Funge {


Unefunge93Strategy::Unefunge93Strategy(FungeRunner& r) :
	FungeStrategy(r)
{
	r.setSemantic('0', std::bind(&Unefunge93Strategy::instructionPush, this, std::placeholders::_1, 0));
	r.setSemantic('1', std::bind(&Unefunge93Strategy::instructionPush, this, std::placeholders::_1, 1));
	r.setSemantic('2', std::bind(&Unefunge93Strategy::instructionPush, this, std::placeholders::_1, 2));
	r.setSemantic('3', std::bind(&Unefunge93Strategy::instructionPush, this, std::placeholders::_1, 3));
	r.setSemantic('4', std::bind(&Unefunge93Strategy::instructionPush, this, std::placeholders::_1, 4));
	r.setSemantic('5', std::bind(&Unefunge93Strategy::instructionPush, this, std::placeholders::_1, 5));
	r.setSemantic('6', std::bind(&Unefunge93Strategy::instructionPush, this, std::placeholders::_1, 6));
	r.setSemantic('7', std::bind(&Unefunge93Strategy::instructionPush, this, std::placeholders::_1, 7));
	r.setSemantic('8', std::bind(&Unefunge93Strategy::instructionPush, this, std::placeholders::_1, 8));
	r.setSemantic('9', std::bind(&Unefunge93Strategy::instructionPush, this, std::placeholders::_1, 9));
	// Flow Control
	r.setSemantic('<', std::bind(&Unefunge93Strategy::instructionWest, this, std::placeholders::_1));
	r.setSemantic('>', std::bind(&Unefunge93Strategy::instructionEast, this, std::placeholders::_1));
	r.setSemantic('@', std::bind(&Unefunge93Strategy::instructionStop, this, std::placeholders::_1));
	r.setSemantic('#', std::bind(&Unefunge93Strategy::instructionTrampoline, this, std::placeholders::_1));
	r.setSemantic('_', std::bind(&Unefunge93Strategy::instructionIf, this, std::placeholders::_1));
	r.setSemantic('?', std::bind(&Unefunge93Strategy::instructionGoAway, this, std::placeholders::_1));
	// Arithmetic Operators
	r.setSemantic('!', std::bind(&Unefunge93Strategy::instructionNot, this, std::placeholders::_1));
	r.setSemantic('%', std::bind(&Unefunge93Strategy::instructionRemainder, this, std::placeholders::_1));
	r.setSemantic('*', std::bind(&Unefunge93Strategy::instructionMultiply, this, std::placeholders::_1));
	r.setSemantic('+', std::bind(&Unefunge93Strategy::instructionAdd, this, std::placeholders::_1));
	r.setSemantic('-', std::bind(&Unefunge93Strategy::instructionSubtract, this, std::placeholders::_1));
	r.setSemantic('/', std::bind(&Unefunge93Strategy::instructionDivide, this, std::placeholders::_1));
	r.setSemantic('`', std::bind(&Unefunge93Strategy::instructionGreater, this, std::placeholders::_1));
	// Stack Operators
	r.setSemantic('$', std::bind(&Unefunge93Strategy::instructionPop, this, std::placeholders::_1));
	r.setSemantic(':', std::bind(&Unefunge93Strategy::instructionDuplicate, this, std::placeholders::_1));
	r.setSemantic('\\', std::bind(&Unefunge93Strategy::instructionSwap, this, std::placeholders::_1));
	// Input
	r.setSemantic('&', std::bind(&Unefunge93Strategy::instructionNumIn, this, std::placeholders::_1));
	r.setSemantic('~', std::bind(&Unefunge93Strategy::instructionCharIn, this, std::placeholders::_1));
	r.setSemantic('\"', std::bind(&Unefunge93Strategy::instructionString, this, std::placeholders::_1));
	// Output
	r.setSemantic('.', std::bind(&Unefunge93Strategy::instructionNumOut, this, std::placeholders::_1));
	r.setSemantic(',', std::bind(&Unefunge93Strategy::instructionCharOut, this, std::placeholders::_1));
	// Self-Modifying
	r.setSemantic('g', std::bind(&Unefunge93Strategy::instructionGet, this, std::placeholders::_1));
	r.setSemantic('p', std::bind(&Unefunge93Strategy::instructionPut, this, std::placeholders::_1));
}

bool Unefunge93Strategy::instructionPush(inst_t i, int n){
	(void)i;
	stack.top().push(n);
	return true;
}

bool Unefunge93Strategy::instructionWest(inst_t i){
	(void)i;
	ip.setDelta(Vector{-1});
	return true;
}

bool Unefunge93Strategy::instructionEast(inst_t i){
	(void)i;
	ip.setDelta(Vector{1});
	return true;
}

bool Unefunge93Strategy::instructionStop(inst_t i){
	(void)i;
	ip.stop();
	return true;
}

bool Unefunge93Strategy::instructionTrampoline(inst_t i){
	(void)i;
	ip.next();
	return true;
}

bool Unefunge93Strategy::instructionIf(inst_t i){
	(void)i;
	if(stack.top().pop() == 0){
		ip.setDelta(Vector{1});
	}else{
		ip.setDelta(Vector{-1});
	}
	return true;
}

bool Unefunge93Strategy::instructionGoAway(inst_t i){
	(void)i;
	size_t d = funge_config.dimensions*2;
	int r = random(0, d-1);
	Vector v;
	if(r & 1){
		v.set(r>>1, -1);
	}else{
		v.set(r>>1, 1);
	}
	ip.setDelta(v);
	return true;
}

bool Unefunge93Strategy::instructionNot(inst_t i){
	(void)i;
	stack.top().push(!stack.top().pop());
	return true;
}

bool Unefunge93Strategy::instructionRemainder(inst_t i){
	(void)i;
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	if(a == 0){
		stack.top().push(0);
	}else{
		stack.top().push(b%a);
	}
	return true;
}

bool Unefunge93Strategy::instructionMultiply(inst_t i){
	(void)i;
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	stack.top().push(b*a);
	return true;
}

bool Unefunge93Strategy::instructionAdd(inst_t i){
	(void)i;
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	stack.top().push(b+a);
	return true;
}

bool Unefunge93Strategy::instructionSubtract(inst_t i){
	(void)i;
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	stack.top().push(b-a);
	return true;
}

bool Unefunge93Strategy::instructionDivide(inst_t i){
	(void)i;
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	if(a == 0){
		stack.top().push(0);
	}else{
		stack.top().push(b/a);
	}
	return true;
}

bool Unefunge93Strategy::instructionGreater(inst_t i){
	(void)i;
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	if(b > a){
		stack.top().push(1);
	}else{
		stack.top().push(0);
	}
	return true;
}

bool Unefunge93Strategy::instructionPop(inst_t i){
	(void)i;
	stack.top().pop();
	return true;
}

bool Unefunge93Strategy::instructionDuplicate(inst_t i){
	(void)i;
	stack_t x = stack.top().pop();
	stack.top().push(x);
	stack.top().push(x);
	return true;
}

bool Unefunge93Strategy::instructionSwap(inst_t i){
	(void)i;
	stack_t a = stack.top().pop();
	stack_t b = stack.top().pop();
	stack.top().push(a);
	stack.top().push(b);
	return true;
}

bool Unefunge93Strategy::instructionNumIn(inst_t i){
	(void)i;
	stack_t num = 0;
	char c = getchar();
	if(c == EOF){
		ip.reflect();
		return true;
	}
	while(c < '0' || c > '9'){
		c = getchar();
		if(c == EOF){
			ip.reflect();
			return true;
		}
	}
	while(c >= '0' && c <= '9'){
		num = (num*10) + (c-'0');
		c = getchar();
		if(c == EOF){
			ip.reflect();
			return true;
		}
	}
	ungetc(c, stdin);
	stack.top().push(num);
	return true;
}

bool Unefunge93Strategy::instructionCharIn(inst_t i){
	(void)i;
	int q = getchar();
	if(q == EOF){
		ip.reflect();
		return true;
	}
	if(q == 13){
		q = getchar();
		if(q == EOF){
			ip.reflect();
			return true;
		}
	}
	stack.top().push(q);
	return true;
}

bool Unefunge93Strategy::instructionString(inst_t i){
	(void)i;
	runner.setState(runner.getStringState());
	return true;
}

bool Unefunge93Strategy::instructionCharOut(inst_t i){
	(void)i;
	stack_t x = stack.top().pop();
	if(x == 10){
		std::cout << std::endl;
	}else{
		std::cout << static_cast<char>(x);
	}
	return true;
}

bool Unefunge93Strategy::instructionNumOut(inst_t i){
	(void)i;
	stack_t x = stack.top().pop();
	std::cout << static_cast<int>(x) << ' ';
	return true;
}

bool Unefunge93Strategy::instructionGet(inst_t i){
	(void)i;
	const Vector& storage = ip.getStorage();
	Vector v = popVector(stack.top());
	stack.top().push(static_cast<stack_t>(field.get(v+storage)));
	return true;
}

bool Unefunge93Strategy::instructionPut(inst_t i){
	(void)i;
	const Vector& storage = ip.getStorage();
	Vector v = popVector(stack.top());
	field.set(v+storage, stack.top().pop());
	return true;
}

FungeStrategy* Unefunge93Strategy::clone(FungeRunner& r) const{
	return new Unefunge93Strategy(r);
}

}
