/**
 * @file Befunge98Strategy.cpp
 * Strategy for Befunge-98 commands.
 * @author Conlan Wesson
 */

#include "Befunge98Strategy.h"
#include "FungeRunner.h"
#include "FungeConfig.h"

namespace Funge {


Befunge98Strategy::Befunge98Strategy(FungeRunner& r) :
	FungeStrategy(r)
{
	r.pushSemantic('[', std::bind(&Befunge98Strategy::instructionLeft, this));
	r.pushSemantic(']', std::bind(&Befunge98Strategy::instructionRight, this));
	r.pushSemantic('w', std::bind(&Befunge98Strategy::instructionCompare, this));
}

bool Befunge98Strategy::instructionLeft(){
	ip.left();
	if(funge_config.switchmode){
		ip.set(']');
	}
	return true;
}

bool Befunge98Strategy::instructionRight(){
	ip.right();
	if(funge_config.switchmode){
		ip.set('[');
	}
	return true;
}

bool Befunge98Strategy::instructionCompare(){
	stack_t b = stack.top().pop();
	stack_t a = stack.top().pop();
	if(a < b){
		ip.left();
	}else if(a > b){
		ip.right();
	}
	return true;
}

FungeStrategy* Befunge98Strategy::clone(FungeRunner& r) const{
	return new Befunge98Strategy(r);
}

}
