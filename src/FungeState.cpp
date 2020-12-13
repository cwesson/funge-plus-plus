/**
 * @file FungeState.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeState.h"

namespace Funge {

FungeState::FungeState(FungeRunner& r, StackStack& s, InstructionPointer& i) :
	runner(r),
	stack(s),
	ip(i)
{
	
}

FungeRunner& FungeState::getRunner(){
	return runner;
}

}
