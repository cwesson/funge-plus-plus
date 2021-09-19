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
	for(auto i : strategy->instructions()){
		auto exist = semantics.find(i);
		if(exist == semantics.cend()){
			semantics[i] = std::stack<FungeStrategy*>();
		}
		semantics[i].push(strategy);
	}
	return true;
}

bool FungeStateNormal::execute(inst_t i){
	bool done = false;
	if(i != ' '){
		auto found = semantics.find(i);
		if(found != semantics.cend()){
			done = (*found->second.top())(i);
		}
	}
	return done;
}

}
