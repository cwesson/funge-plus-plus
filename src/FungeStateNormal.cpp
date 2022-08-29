/**
 * @file FungeStateNormal.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeStateNormal.h"
#include "FungeConfig.h"
#include "Unefunge93Strategy.h"
#include "Unefunge98Strategy.h"
#include "Befunge93Strategy.h"
#include "Befunge98Strategy.h"
#include "Trefunge98Strategy.h"
#include "FishStrategy.h"
#include "StarfishStrategy.h"
#include "FungeUniverse.h"

namespace Funge {

FungeStateNormal::FungeStateNormal(FungeRunner& r) :
	FungeState(r),
	strategies(),
	semantics()
{
	if(r.getUniverse().standard() == Funge::FUNGE_FISH){
		load(new FishStrategy(runner));
	}else if(r.getUniverse().standard() == Funge::FUNGE_STARFISH){
		load(new StarfishStrategy(runner));
	}else{
		if(r.getUniverse().dimensions() >= 1){
			if(r.getUniverse().standard() >= Funge::FUNGE_93){
				load(new Unefunge93Strategy(runner));
			}
			if(r.getUniverse().standard() >= Funge::FUNGE_98){
				load(new Unefunge98Strategy(runner));
			}
		}
		if(r.getUniverse().dimensions() >= 2){
			if(r.getUniverse().standard() >= Funge::FUNGE_93){
				load(new Befunge93Strategy(runner));
			}
			if(r.getUniverse().standard() >= Funge::FUNGE_98){
				load(new Befunge98Strategy(runner));
			}
		}
		if(r.getUniverse().dimensions() >= 3){
			if(r.getUniverse().standard() >= Funge::FUNGE_98){
				load(new Trefunge98Strategy(runner));
			}
		}
	}
}

FungeStateNormal::FungeStateNormal(const FungeStateNormal& orig, FungeRunner& r) :
	FungeState(r),
	strategies(),
	semantics()
{
	for(auto s : orig.strategies){
		load(s->clone(runner));
	}
}

FungeStateNormal::~FungeStateNormal(){
	while(strategies.size() > 0){
		delete strategies.back();
		strategies.pop_back();
	}
}

bool FungeStateNormal::load(FungeStrategy* strategy){
	strategies.push_back(strategy);
	return true;
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
