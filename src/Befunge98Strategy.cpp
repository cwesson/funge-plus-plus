/**
 * @file Befunge98Strategy.cpp
 * Strategy for Befunge-98 commands.
 * @author Conlan Wesson
 */

#include "Befunge98Strategy.h"
#include "FungeRunner.h"

namespace Funge {


Befunge98Strategy::Befunge98Strategy(FungeRunner& r) :
	FungeStrategy(r)
{
	r.pushSemantic('[', std::bind(&Befunge98Strategy::instructionLeft, this), FungeSemantic::MOVEMENT);
	r.pushSemantic(']', std::bind(&Befunge98Strategy::instructionRight, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('w', std::bind(&Befunge98Strategy::instructionCompare, this));
}

FungeError Befunge98Strategy::instructionLeft(){
	ip.left();
	if(runner.isMode(FUNGE_MODE_SWITCH)){
		ip.put(']');
	}
	return ERROR_NONE;
}

FungeError Befunge98Strategy::instructionRight(){
	ip.right();
	if(runner.isMode(FUNGE_MODE_SWITCH)){
		ip.put('[');
	}
	return ERROR_NONE;
}

FungeError Befunge98Strategy::instructionCompare(){
	stack_t b = stack.top().pop();
	stack_t a = stack.top().pop();
	if(a < b){
		ip.left();
	}else if(a > b){
		ip.right();
	}
	return ERROR_NONE;
}

FungeStrategy* Befunge98Strategy::clone(FungeRunner& r) const{
	return new Befunge98Strategy(r);
}

}
