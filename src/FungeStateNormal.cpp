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

namespace Funge {

FungeStateNormal::FungeStateNormal(FungeRunner& r) :
	FungeState(r),
	strategies(),
	semantics()
{
	if(funge_config.dimensions >= 1){
		if(funge_config.standard >= 93){
			load(new Unefunge93Strategy(runner));
		}
		if(funge_config.standard >= 98){
			load(new Unefunge98Strategy(runner));
		}
	}
	if(funge_config.dimensions >= 2){
		if(funge_config.standard >= 93){
			load(new Befunge93Strategy(runner));
		}
		if(funge_config.standard >= 98){
			load(new Befunge98Strategy(runner));
		}
	}
	if(funge_config.dimensions >= 3){
		if(funge_config.standard >= 98){
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

void FungeStateNormal::setSemantic(inst_t i, std::function<bool(inst_t)> func){
	auto exist = semantics.find(i);
	if(exist == semantics.cend()){
		semantics[i] = std::stack<std::function<bool(inst_t)>>();
	}
	semantics[i].push(func);
}

void FungeStateNormal::popSemantic(inst_t i){
	auto exist = semantics.find(i);
	if(exist != semantics.cend()){
		semantics[i].pop();
	}
}

bool FungeStateNormal::execute(inst_t i){
	bool done = false;
	if(i != ' '){
		auto found = semantics.find(i);
		if(found != semantics.cend()){
			if(found->second.size() > 0){
				done = found->second.top()(i);
			}
		}
	}
	return done;
}

}
