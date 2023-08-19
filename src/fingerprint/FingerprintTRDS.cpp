/**
 * @file FingerprintTRDS.cpp
 * IP travel in time and space.
 * @author Conlan Wesson
 */

#include "FingerprintTRDS.h"
#include "FungeUniverse.h"

namespace Funge {

FingerprintTRDS::FingerprintTRDS(FungeRunner& r) :
	Fingerprint(r, {'P'})
{}

FungeError FingerprintTRDS::execute(inst_t cmd){
	switch(cmd){
		case 'P':{
			stack.top().push(runner.getUniverse().getAge());
		} break;
		default:
			return ERROR_UNIMP;
	}
	return ERROR_NONE;
}

}
