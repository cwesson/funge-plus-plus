/**
 * @file FingerprintDynamic.cpp
 * Dynamic Funge.
 * @author Conlan Wesson
 */

#include "FingerprintDynamic.h"

namespace Funge {

FingerprintDynamic::FingerprintDynamic(FungeRunner& r, FungeRunner* c) :
	Fingerprint(r, {'F', 'K', 'O', 'R', 'X'}),
	caller(c)
{

}

bool FingerprintDynamic::execute(inst_t cmd){
	if(caller != nullptr){
		switch(cmd){
			case 'F':
				caller->getIP().next();
				break;
			case 'K':{
				stack_t u = stack.top().pop();
				if(u < 0){
					ip.reflect();
					break;
				}
				stack_t x = stack.top().get(u+1);
				stack.top().push(x);
			} break;
			case 'O':{
				stack_t u = stack.top().pop();
				stack_t count = u;
				if(u < 0){
					count = -u;
				}
				stack_t pops[count+1];
				for(stack_t i = 0; i <= count; ++i){
					pops[i] = stack.top().pop();
				}
				if(u < 0){
					stack.top().push(pops[0]);
					for(stack_t i = count; i > 0; --i){
						stack.top().push(pops[i]);
					}
				}else{
					for(stack_t i = count-1; i >= 0; --i){
						stack.top().push(pops[i]);
					}
					stack.top().push(pops[count]);
				}
			} break;
			case 'R':
				caller->getIP().reflect();
				break;
			case 'X':
				caller->getIP().stop();
				runner.getIP().stop();
				break;
			default:
				return false;
		}
	}
	return true;
}

}
