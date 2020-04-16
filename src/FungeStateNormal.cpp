/**
 * @file FungeStateNormal.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeStateNormal.h"
#include "FungeRunner.h"

namespace Funge {

FungeStateNormal::FungeStateNormal(FungeRunner& r, StackStack& s, FungeStrategy* strat) :
	FungeState(r, s),
	strategy(strat)
{
	
}

bool FungeStateNormal::execute(inst_t i){
	if(i == ' '){
		return false;
	}else if(i == '\"'){
		runner.setState(runner.getStringState());
	}else{
		return strategy->execute(i);
	}
	return true;
}

}
