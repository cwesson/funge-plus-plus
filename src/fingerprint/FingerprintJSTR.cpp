/**
 * @file FingerprintJSTR.cpp
 * 3d string vectors.
 * @author Conlan Wesson
 */

#include "FingerprintJSTR.h"
#include "FungeUtilities.h"

namespace Funge {

FingerprintJSTR::FingerprintJSTR(FungeRunner& r) :
	Fingerprint(r, {'G', 'P'})
{}

FungeError FingerprintJSTR::execute(inst_t cmd){
	switch(cmd){
		case 'G':{
			stack_t n = stack.top().pop();
			Vector va = popVector(runner);
			Vector vd = popVector(runner);
			Vector pos = va + ip.getStorage();
			stack.top().push(0);
			for( ; n > 0; --n){
				stack.top().push(field.get(pos));
				pos += vd;
			}
		} break;
		case 'P':{
			stack_t n = stack.top().pop();
			Vector va = popVector(runner);
			Vector vd = popVector(runner);
			Vector pos = va + ip.getStorage();
			for( ; n > 0; --n){
				field.put(pos, stack.top().pop());
				pos += vd;
			}
		} break;
		default:
			return ERROR_UNIMP;
	}
	return ERROR_NONE;
}

}
