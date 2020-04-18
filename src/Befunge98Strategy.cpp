/**
 * @file Befunge98Strategy.cpp
 * Strategy for Befunge-98 commands.
 * @author Conlan Wesson
 */

#include "Befunge98Strategy.h"
#include <iostream>

namespace Funge {


Befunge98Strategy::Befunge98Strategy(Field& f, InstructionPointer& i, StackStack& s) :
	Unefunge98Strategy(f, i, s)
{
	
}

bool Befunge98Strategy::execute(inst_t cmd){
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
		case '?':{
			int r = random()%4;
			switch(r){
				case 0:
					ip.setDelta(Vector{0, 1}); break;
				case 1:
					ip.setDelta(Vector{-1, 0}); break;
				case 2:
					ip.setDelta(Vector{1, 0}); break;
				case 3:
					ip.setDelta(Vector{0, -1}); break;
			}
		} break;
		
		case '[':
			ip.left();
			break;
		case ']':
			ip.right();
			break;
		
		case 'w':{
			stack_t b = stack.top().pop();
			stack_t a = stack.top().pop();
			if(a < b){
				ip.left();
			}else if(a > b){
				ip.right();
			}
		} break;
		
		default:
			return Unefunge98Strategy::execute(cmd);
	}
	return true;
}

}
