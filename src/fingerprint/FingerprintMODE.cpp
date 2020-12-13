/**
 * @file FingerprintMODE.cpp
 * Standard Modes.
 * @author Conlan Wesson
 */

#include "FingerprintMODE.h"
#include "FungeConfig.h"
#include <cmath>

namespace Funge {

FingerprintMODE::FingerprintMODE(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s, {'H', 'I', 'Q', 'S'})
{}

bool FingerprintMODE::execute(inst_t cmd){
	switch(cmd){
		case 'H':{
			funge_config.hovermode = !funge_config.hovermode;
		} break;
		case 'I':{
			funge_config.invertmode = !funge_config.invertmode;
		} break;
		case 'Q':{
			funge_config.queuemode = !funge_config.queuemode;
		} break;
		case 'S':{
			funge_config.switchmode = !funge_config.switchmode;
		} break;
		default:
			return false;
	}
	return true;
}

}
