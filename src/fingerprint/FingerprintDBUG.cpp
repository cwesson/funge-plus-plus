/**
 * @file FingerprintDBUG.cpp
 * Software debugging.
 * @author Conlan Wesson
 */

#include "FingerprintDBUG.h"
#include "FungeUtilities.h"
#include "FungeUniverse.h"

namespace Funge {

FingerprintDBUG::FingerprintDBUG(FungeRunner& r) :
	Fingerprint(r, {'A', 'B', 'D', 'E', 'W'}),
	dbg(nullptr)
{}

void FingerprintDBUG::activate(){
	dbg = &runner.getUniverse().getDebugger();
}

bool FingerprintDBUG::execute(inst_t cmd){
	switch(cmd){
		case 'A':{
			Vector v = popVector(runner);
			dbg->addBreakpoint(v);
		} break;
		case 'B':{
			dbg->swbreak(runner);
		} break;
		case 'D':{
			runner.getUniverse().clearMode(FUNGE_MODE_DEBUG);
		} break;
		case 'E':{
			runner.getUniverse().setMode(FUNGE_MODE_DEBUG);
		} break;
		case 'W':{
			Vector v = popVector(runner);
			dbg->addWatchpoint(v);
		} break;
		default:
			return false;
	}
	return true;
}

}
