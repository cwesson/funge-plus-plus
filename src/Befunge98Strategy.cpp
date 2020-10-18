/**
 * @file Befunge98Strategy.cpp
 * Strategy for Befunge-98 commands.
 * @author Conlan Wesson
 */

#include "Befunge98Strategy.h"
#include "FungeConfig.h"

namespace Funge {


Befunge98Strategy::Befunge98Strategy(Field& f, InstructionPointer& i, StackStack& s, FungeState& t) :
	FungeStrategy(f, i, s, t, {'[', ']', 'w'})
{
	
}

bool Befunge98Strategy::execute(inst_t cmd){
	switch(cmd){
		case '[':
			ip.left();
			if(funge_config.switchmode){
				ip.set(']');
			}
			break;
		case ']':
			ip.right();
			if(funge_config.switchmode){
				ip.set('[');
			}
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
			return false;
	}
	return true;
}

}
