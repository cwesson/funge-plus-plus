/**
 * @file FungeState.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeState.h"
#include "FungeRunner.h"

namespace Funge {

FungeState::FungeState(FungeRunner& r) :
	runner(r),
	stack(r.getStack()),
	ip(r.getIP())
{
	
}

}
