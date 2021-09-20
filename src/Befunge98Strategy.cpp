/**
 * @file Befunge98Strategy.cpp
 * Strategy for Befunge-98 commands.
 * @author Conlan Wesson
 */

#include "Befunge98Strategy.h"
#include "FungeRunner.h"
#include "FungeConfig.h"

namespace Funge {


Befunge98Strategy::Befunge98Strategy(FungeRunner& r) :
	FungeStrategy(r)
{
	for(auto i : {'[', ']', 'w'}){
		r.setSemantic(i, std::bind(&Befunge98Strategy::operator(), this, std::placeholders::_1));
	}
}

bool Befunge98Strategy::operator()(inst_t cmd){
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

FungeStrategy* Befunge98Strategy::clone(FungeRunner& r) const{
	return new Befunge98Strategy(r);
}

}
