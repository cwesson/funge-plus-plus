/**
 * @file FungeStateNormal.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeStateNormal.h"
#include "FungeConfig.h"
#include "FungeUniverse.h"

namespace Funge {

FungeStateNormal::FungeStateNormal(FungeRunner& r) :
	FungeState(r),
	semantics()
{
}

void FungeStateNormal::pushSemantic(inst_t i, FungeSemantic* func){
	auto exist = semantics.find(i);
	if(exist == semantics.cend()){
		semantics[i] = std::stack<FungeSemantic*>();
	}
	semantics[i].push(func);
}

FungeSemantic* FungeStateNormal::popSemantic(inst_t i){
	FungeSemantic* ret = nullptr;
	auto exist = semantics.find(i);
	if(exist != semantics.cend() && semantics[i].size() > 0){
		ret = semantics[i].top();
		semantics[i].pop();
	}
	return ret;
}

FungeSemantic* FungeStateNormal::getSemantic(inst_t i){
	FungeSemantic* ret = nullptr;
	auto exist = semantics.find(i);
	if(exist != semantics.cend() && semantics[i].size() > 0){
		ret = semantics[i].top();
	}
	return ret;
}

FungeError FungeStateNormal::execute(inst_t i){
	FungeError done = ERROR_UNIMP;
	auto found = semantics.find(i);
	if(found != semantics.cend() && found->second.size() > 0){
		FungeSemantic& sem = *found->second.top();
		if(runner.isMode(FUNGE_MODE_DIVE) && !sem.isMovement()){
			done = ERROR_SKIP;
		}else{
			done = sem();
		}
	}
	return done;
}

}
