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
	r.setSemantic('^', std::bind(&Befunge93Strategy::instructionNorth, this, std::placeholders::_1));
	r.setSemantic('v', std::bind(&Befunge93Strategy::instructionSouth, this, std::placeholders::_1));
	r.setSemantic('|', std::bind(&Befunge93Strategy::instructionIf, this, std::placeholders::_1));
}

bool Befunge93Strategy::instructionNorth(inst_t i){
	(void)i;
	ip.setDelta(Vector{0, -1});
	return true;
}

bool Befunge93Strategy::instructionSouth(inst_t i){
	(void)i;
	ip.setDelta(Vector{0, 1});
	return true;
}

bool Befunge93Strategy::instructionIf(inst_t i){
	(void)i;
	if(stack.top().pop() == 0){
		ip.setDelta(Vector{0, 1});
	}else{
		ip.setDelta(Vector{0, -1});
	}
	return true;
}

FungeStrategy* Befunge93Strategy::clone(FungeRunner& r) const{
	return new Befunge93Strategy(r);
}

}
