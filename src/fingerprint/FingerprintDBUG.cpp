/**
 * @file FingerprintDBUG.cpp
 * Software debugging.
 * @author Conlan Wesson
 */

#include "FingerprintDBUG.h"
#include "FungeUtilities.h"
#include "FungeConfig.h"

namespace Funge {

FingerprintDBUG::FingerprintDBUG(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s, {'A', 'B', 'D', 'E', 'W'}),
	dbg(nullptr)
{}

void FingerprintDBUG::activate(){
	dbg = FungeDebugger::getInstance();
}

bool FingerprintDBUG::execute(inst_t cmd){
	switch(cmd){
		case 'A':{
			Vector v = popVector(stack.top());
			dbg->addBreakpoint(v);
		} break;
		case 'B':{
			dbg->swbreak(field, stack, ip);
		} break;
		case 'D':{
			funge_config.debug = false;
		} break;
		case 'E':{
			funge_config.debug = true;
		} break;
		case 'W':{
			Vector v = popVector(stack.top());
			dbg->addWatchpoint(v);
		} break;
		default:
			return false;
	}
	return true;
}

}
