/**
 * @file FungeStateNormal.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeStateNormal.h"
#include "FungeRunner.h"
#include "FungeConfig.h"
#include "Unefunge93Strategy.h"
#include "Unefunge98Strategy.h"
#include "Befunge93Strategy.h"
#include "Befunge98Strategy.h"
#include "Trefunge98Strategy.h"

namespace Funge {

FungeStateNormal::FungeStateNormal(FungeRunner& r, Field& f, StackStack& s, InstructionPointer& i) :
	FungeState(r, s, i),
	strategies(),
	semantics()
{
	if(funge_config.dimensions >= 1){
		if(funge_config.standard >= 93){
			load(new Unefunge93Strategy(f, i, s, *this));
		}
		if(funge_config.standard >= 98){
			load(new Unefunge98Strategy(f, i, s, *this));
		}
	}
	if(funge_config.dimensions >= 2){
		if(funge_config.standard >= 93){
			load(new Befunge93Strategy(f, i, s, *this));
		}
		if(funge_config.standard >= 98){
			load(new Befunge98Strategy(f, i, s, *this));
		}
	}
	if(funge_config.dimensions >= 3){
		if(funge_config.standard >= 98){
			load(new Trefunge98Strategy(f, i, s, *this));
		}
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
	if(i == ' '){
		return false;
	}else if(i == '\"'){
		runner.setState(runner.getStringState());
	}else{
		bool done = false;
		auto found = semantics.find(i);
		if(found != semantics.cend()){
			done = found->second.top()->execute(i);
		}
		return done;
	}
	return true;
}

}
