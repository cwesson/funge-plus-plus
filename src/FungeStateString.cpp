/**
 * @file FungeStateString.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeStateString.h"
#include "FungeRunner.h"

namespace Funge {

FungeStateString::FungeStateString(FungeRunner& r, StackStack& s) :
	FungeState(r, s)
{
	
}

bool FungeStateString::execute(inst_t i){
	if(i == '\"'){
		runner.setState(runner.getNormalState());
	}else{
		stack.top().push(static_cast<int>(i));
	}
	return true;
}

}
