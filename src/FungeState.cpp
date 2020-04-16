/**
 * @file FungeState.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeState.h"

namespace Funge {

FungeState::FungeState(FungeRunner& r, StackStack& s) :
	runner(r),
	stack(s)
{
	
}

}
