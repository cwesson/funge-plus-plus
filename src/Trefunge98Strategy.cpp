/**
 * @file Trefunge98Strategy.cpp
 * Strategy for Trefunge-98 commands.
 * @author Conlan Wesson
 */

#include "Trefunge98Strategy.h"
#include "FungeRunner.h"
#include "FungeUniverse.h"

namespace Funge {


Trefunge98Strategy::Trefunge98Strategy(FungeRunner& r) :
	FungeStrategy(r)
{
	r.pushSemantic('h', std::bind(&Trefunge98Strategy::instructionHigh, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('l', std::bind(&Trefunge98Strategy::instructionLow, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('m', std::bind(&Trefunge98Strategy::instructionIf, this));
}

FungeError Trefunge98Strategy::instructionHigh(){
	if(!runner.getUniverse().invertHL()){
		ip.setDelta(Vector{0, 0, 1});
	}else{
		ip.setDelta(Vector{0, 0, -1});
	}
	return ERROR_NONE;
}

FungeError Trefunge98Strategy::instructionLow(){
	if(!runner.getUniverse().invertHL()){
		ip.setDelta(Vector{0, 0, -1});
	}else{
		ip.setDelta(Vector{0, 0, 1});
	}
	return ERROR_NONE;
}

FungeError Trefunge98Strategy::instructionIf(){
	if(stack.top().pop() == 0){
		ip.setDelta(Vector{0, 0, 1});
	}else{
		ip.setDelta(Vector{0, 0, -1});
	}
	return ERROR_NONE;
}

FungeStrategy* Trefunge98Strategy::clone(FungeRunner& r) const{
	return new Trefunge98Strategy(r);
}

}
