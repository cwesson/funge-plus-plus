/**
 * @file FingerprintMVRS.cpp
 * Multiverse extension.
 * @author Conlan Wesson
 */

#include "FingerprintMVRS.h"
#include "FungeMultiverse.h"
#include "FungeUtilities.h"

namespace Funge {

FingerprintMVRS::FingerprintMVRS(FungeRunner& r) :
	Fingerprint(r, {'B', 'C', 'F', 'G', 'J', 'N', 'P'})
{}

bool FingerprintMVRS::execute(inst_t cmd){
	const FungeMultiverse& multi = FungeMultiverse::getInstance();
	const FungeUniverse& universe = runner.getUniverse();
	switch(cmd){
		case 'C':{
			stack.top().push(multi.size());
		} break;
		case 'N':{
			pushString(stack.top(), universe.getName());
		} break;
		default:
			return false;
	}
	return true;
}

}
