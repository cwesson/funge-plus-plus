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
	for(auto i : {'^', 'v', '|'}){
		r.setSemantic(i, std::bind(&Befunge93Strategy::operator(), this, std::placeholders::_1));
	}
}

bool Befunge93Strategy::operator()(inst_t cmd){
	switch(cmd){
		case '^':
			ip.setDelta(Vector{0, -1}); break;
		case 'v':
			ip.setDelta(Vector{0, 1}); break;
		case '|':
			if(stack.top().pop() == 0){
				ip.setDelta(Vector{0, 1});
			}else{
				ip.setDelta(Vector{0, -1});
			}
			break;

		default:
			return false;
	}
	return true;
}

FungeStrategy* Befunge93Strategy::clone(FungeRunner& r) const{
	return new Befunge93Strategy(r);
}

}
