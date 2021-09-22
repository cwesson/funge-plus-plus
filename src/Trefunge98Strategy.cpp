/**
 * @file Trefunge98Strategy.cpp
 * Strategy for Trefunge-98 commands.
 * @author Conlan Wesson
 */

#include "Trefunge98Strategy.h"
#include "FungeRunner.h"
#include "FungeConfig.h"

namespace Funge {


Trefunge98Strategy::Trefunge98Strategy(FungeRunner& r) :
	FungeStrategy(r)
{
	r.setSemantic('h', std::bind(&Trefunge98Strategy::instructionHigh, this));
	r.setSemantic('l', std::bind(&Trefunge98Strategy::instructionLow, this));
	r.setSemantic('m', std::bind(&Trefunge98Strategy::instructionIf, this));
}

bool Trefunge98Strategy::instructionHigh(){
	if(!funge_config.inverthl){
		ip.setDelta(Vector{0, 0, 1});
	}else{
		ip.setDelta(Vector{0, 0, -1});
	}
	return true;
}

bool Trefunge98Strategy::instructionLow(){
	if(!funge_config.inverthl){
		ip.setDelta(Vector{0, 0, -1});
	}else{
		ip.setDelta(Vector{0, 0, 1});
	}
	return true;
}

bool Trefunge98Strategy::instructionIf(){
	if(stack.top().pop() == 0){
		ip.setDelta(Vector{0, 0, 1});
	}else{
		ip.setDelta(Vector{0, 0, -1});
	}
	return true;
}

FungeStrategy* Trefunge98Strategy::clone(FungeRunner& r) const{
	return new Trefunge98Strategy(r);
}

}
