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
	for(auto i : {'h', 'l', 'm'}){
		r.setSemantic(i, std::bind(&Trefunge98Strategy::operator(), this, std::placeholders::_1));
	}
}

bool Trefunge98Strategy::operator()(inst_t cmd){
	switch(cmd){
		case 'h':
			if(!funge_config.inverthl){
				ip.setDelta(Vector{0, 0, 1});
			}else{
				ip.setDelta(Vector{0, 0, -1});
			}
			break;
		case 'l':
			if(!funge_config.inverthl){
				ip.setDelta(Vector{0, 0, -1});
			}else{
				ip.setDelta(Vector{0, 0, 1});
			}
			break;
		case 'm':
			if(stack.top().pop() == 0){
				ip.setDelta(Vector{0, 0, 1});
			}else{
				ip.setDelta(Vector{0, 0, -1});
			}
			break;
		
		default:
			return false;
	}
	return true;
}

FungeStrategy* Trefunge98Strategy::clone(FungeRunner& r) const{
	return new Trefunge98Strategy(r);
}

}
