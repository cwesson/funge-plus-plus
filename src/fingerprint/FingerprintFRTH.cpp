/**
 * @file FingerprintFRTH.cpp
 * Some common forth commands.
 * @author Conlan Wesson
 */

#include "FingerprintFRTH.h"

namespace Funge {

FingerprintFRTH::FingerprintFRTH(FungeRunner& r) :
	Fingerprint(r, {'D', 'L', 'O', 'P', 'R'})
{}

FungeError FingerprintFRTH::execute(inst_t cmd){
	FungeError ret = ERROR_NONE;
	switch(cmd){
		case 'D':{
			stack_t n = stack.top().size();
			stack.top().push(n);
		} break;
		case 'L':{
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
		case 'O':{
			stack_t b = stack.top().pop();
			stack_t a = stack.top().pop();
			stack.top().push(a);
			stack.top().push(b);
			stack.top().push(a);
		} break;
		case 'P':{
			stack_t u = stack.top().pop();
			if(u < 0){
				ret = ERROR_UNSPEC;
				break;
			}
			stack_t x = stack.top().get(u+1);
			stack.top().push(x);
		} break;
		case 'R':{
			stack_t c = stack.top().pop();
			stack_t b = stack.top().pop();
			stack_t a = stack.top().pop();
			stack.top().push(b);
			stack.top().push(c);
			stack.top().push(a);
		} break;
		default:
			ret = ERROR_UNIMP;
	}
	return ret;
}

}
