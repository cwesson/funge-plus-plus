/**
 * @file Befunge93Strategy.cpp
 * Strategy for Befunge-93 commands.
 * @author Conlan Wesson
 */

#include "Befunge93Strategy.h"

namespace Funge {


Befunge93Strategy::Befunge93Strategy(Field& f, InstructionPointer& i, StackStack& s, FungeState& t) :
	FungeStrategy(f, i, s, t, {'^', 'v', '|'})
{
	
}

bool Befunge93Strategy::execute(inst_t cmd){
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

}
