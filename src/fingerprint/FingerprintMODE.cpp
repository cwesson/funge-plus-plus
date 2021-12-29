/**
 * @file FingerprintMODE.cpp
 * Standard Modes.
 * @author Conlan Wesson
 */

#include "FingerprintMODE.h"
#include "FungeUniverse.h"
#include <cmath>

namespace Funge {

FingerprintMODE::FingerprintMODE(FungeRunner& r) :
	Fingerprint(r, {'H', 'I', 'Q', 'S'})
{}

bool FingerprintMODE::execute(inst_t cmd){
	switch(cmd){
		case 'H':{
			runner.getUniverse().toggleMode(FUNGE_MODE_HOVER);
		} break;
		case 'I':{
			runner.getUniverse().toggleMode(FUNGE_MODE_INVERT);
		} break;
		case 'Q':{
			runner.getUniverse().toggleMode(FUNGE_MODE_QUEUE);
		} break;
		case 'S':{
			runner.getUniverse().toggleMode(FUNGE_MODE_SWITCH);
		} break;
		default:
			return false;
	}
	return true;
}

}
