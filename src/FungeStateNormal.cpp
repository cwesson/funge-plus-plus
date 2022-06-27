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
#include "FungeUniverse.h"

namespace Funge {

FungeStateNormal::FungeStateNormal(FungeRunner& r) :
	FungeState(r),
	strategies(),
	semantics()
{
	FungeUniverse& uni = runner.getUniverse();
	if(uni.dimensions() >= 1){
		if(uni.standard() >= 93){
			load(new Unefunge93Strategy(runner));
		}
		if(uni.standard() >= 98){
			load(new Unefunge98Strategy(runner));
		}
	}
	if(uni.dimensions() >= 2){
		if(uni.standard() >= 93){
			load(new Befunge93Strategy(runner));
		}
		if(uni.standard() >= 98){
			load(new Befunge98Strategy(runner));
		}
	}
	if(uni.dimensions() >= 3){
		if(uni.standard() >= 98){
			load(new Trefunge98Strategy(runner));
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

void FungeStateNormal::pushSemantic(inst_t i, semantic_t func){
	auto exist = semantics.find(i);
	if(exist == semantics.cend()){
		semantics[i] = std::stack<semantic_t>();
	}
	semantics[i].push(func);
}

semantic_t FungeStateNormal::popSemantic(inst_t i){
	semantic_t ret = nullptr;
	auto exist = semantics.find(i);
	if(exist != semantics.cend() && semantics[i].size() > 0){
		ret = semantics[i].top();
		semantics[i].pop();
	}
	return ret;
}

semantic_t FungeStateNormal::getSemantic(inst_t i){
	semantic_t ret = nullptr;
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
		done = found->second.top()();
	}
	return done;
}

}
