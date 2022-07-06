/**
 * @file StarfishStrategy.cpp
 * Strategy for *><> commands.
 * @author Conlan Wesson
 */

#include "StarfishStrategy.h"
#include "FungeRunner.h"
#include "FungeUniverse.h"

namespace Funge {

StarfishStrategy::StarfishStrategy(FungeRunner& r) :
	FishStrategy(r),
	fisherstate(FISHER_UP),
	fishercache({1, 0})
{
	r.pushSemantic('`', std::bind(&StarfishStrategy::instructionFisherman, this));
	r.pushSemantic('u', std::bind(&StarfishStrategy::instructionDive, this));
	r.pushSemantic('O', std::bind(&StarfishStrategy::instructionRise, this));
}

FungeError StarfishStrategy::instructionFisherman(){
	if(ip.getDelta().get(1) == 0){
		fishercache = ip.getDelta();
		if(fisherstate == FISHER_UP){
			ip.setDelta(Vector{0, 1});
			fisherstate = FISHER_DOWN;
		}else{
			ip.setDelta(Vector{0, -1});
			fisherstate = FISHER_UP;
		}
	}else{
		ip.setDelta(fishercache);
	}
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionDive(){
	runner.getUniverse().setMode(FUNGE_MODE_DIVE);
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionRise(){
	runner.getUniverse().clearMode(FUNGE_MODE_DIVE);
	return ERROR_NONE;
}

}; // namespace Funge
