/**
 * @file Befunge93Strategy.cpp
 * Strategy for Befunge-93 commands.
 * @author Conlan Wesson
 */

#include "Befunge93Strategy.h"
#include "FungeRunner.h"

namespace Funge {


Befunge93Strategy::Befunge93Strategy(FungeRunner& r) :
	FungeStrategy(r)
{
	r.pushSemantic('^', std::bind(&Befunge93Strategy::instructionNorth, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('v', std::bind(&Befunge93Strategy::instructionSouth, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('|', std::bind(&Befunge93Strategy::instructionIf, this));
}

FungeError Befunge93Strategy::instructionNorth(){
	ip.setDelta(Vector{0, -1});
	return ERROR_NONE;
}

FungeError Befunge93Strategy::instructionSouth(){
	ip.setDelta(Vector{0, 1});
	return ERROR_NONE;
}

FungeError Befunge93Strategy::instructionIf(){
	if(stack.top().pop() == 0){
		ip.setDelta(Vector{0, 1});
	}else{
		ip.setDelta(Vector{0, -1});
	}
	return ERROR_NONE;
}

FungeStrategy* Befunge93Strategy::clone(FungeRunner& r) const{
	return new Befunge93Strategy(r);
}

}
