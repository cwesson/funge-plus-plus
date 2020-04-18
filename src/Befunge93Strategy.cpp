/**
 * @file Befunge93Strategy.cpp
 * Strategy for Befunge-93 commands.
 * @author Conlan Wesson
 */

#include "Befunge93Strategy.h"
#include <iostream>

namespace Funge {


Befunge93Strategy::Befunge93Strategy(Field& f, InstructionPointer& i, StackStack& s) :
	Unefunge93Strategy(f, i, s)
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
			return Unefunge93Strategy::execute(cmd);
	}
	return true;
}

}
