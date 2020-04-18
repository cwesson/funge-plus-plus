/**
 * @file Trefunge98Strategy.cpp
 * Strategy for Trefunge-98 commands.
 * @author Conlan Wesson
 */

#include "Trefunge98Strategy.h"
#include <iostream>

namespace Funge {


Trefunge98Strategy::Trefunge98Strategy(Field& f, InstructionPointer& i, StackStack& s) :
	Befunge98Strategy(f, i, s)
{
	
}

bool Trefunge98Strategy::execute(inst_t cmd){
	switch(cmd){
		case 'h':
			ip.setDelta(Vector{0, 0, -1}); break;
		case 'l':
			ip.setDelta(Vector{0, 0, 1}); break;
		case 'm':
			if(stack.top().pop() == 0){
				ip.setDelta(Vector{0, 0, 1});
			}else{
				ip.setDelta(Vector{0, 0, -1});
			}
			break;
		
		default:
			return Befunge98Strategy::execute(cmd);
	}
	return true;
}

}
