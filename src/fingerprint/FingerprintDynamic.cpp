/**
 * @file FingerprintDynamic.cpp
 * Dynamic Funge.
 * @author Conlan Wesson
 */

#include "FingerprintDynamic.h"
#include "FungeUtilities.h"

namespace Funge {

FingerprintDynamic::FingerprintDynamic(FungeRunner& r, FungeRunner* c) :
	Fingerprint(r, {'B', 'D', 'E', 'F', 'G', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'X'}),
	caller(c)
{

}

FungeError FingerprintDynamic::execute(inst_t cmd){
	FungeError ret = ERROR_NONE;
	if(caller != nullptr){
		switch(cmd){
			case 'B':{
				InstructionPointer& cip = caller->getIP();
				cip.reflect();
				cip.next();
				cip.reflect();
			} break;
			case 'D':{
				Vector v = popVector(runner, &stack.top());
				caller->getIP().setDelta(v);
			} break;
			case 'E':
				stack.top().push(stack.top().size());
				break;
			case 'F':
				caller->getIP().next();
				break;
			case 'G':{
				Field& f = caller->getField();
				Vector v = popVector(runner, &stack.top());
				stack.top().push(f.get(v));
			} break;
			case 'K':{
				stack_t u = stack.top().pop();
				if(u < 0){
					ret = ERROR_UNSPEC;
					break;
				}
				stack_t x = stack.top().get(u+1);
				stack.top().push(x);
			} break;
			case 'L':{
				Vector v = popVector(runner, &stack.top());
				caller->getIP().setPos(v);
			} break;
			case 'M':
				stack.top().push(caller->getMode() >> 12);
				break;
			case 'N':{
				Vector v = caller->getIP().getPos();
				v += caller->getIP().getDelta();
				Field& f = caller->getField();
				stack.top().push(f.get(v));
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
			case 'P':{
				Vector v = popVector(runner, &stack.top());
				stack_t n = stack.top().pop();
				Field& f = caller->getField();
				f.put(v, n);
			} break;
			case 'Q':{
				InstructionPointer& cip = caller->getIP();
				pushVector(*caller, cip.getPos());
				pushVector(*caller, cip.getDelta());
				pushVector(*caller, cip.getStorage());
			} break;
			case 'R':
				caller->getIP().reflect();
				break;
			case 'S':{
				Vector v = popVector(runner, &stack.top());
				caller->getIP().setStorage(v);
			} break;
			case 'X':
				caller->getIP().stop();
				ip.stop();
				break;
			default:
				ret = ERROR_UNIMP;
		}
	}
	return ret;
}

}
