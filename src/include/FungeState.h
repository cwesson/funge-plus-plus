/**
 * @file FungeState.h
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#pragma once

#include "StackStack.h"

namespace Funge {
class FungeRunner;

class FungeState {
	public:
		FungeState(FungeRunner& r, StackStack& s);
		virtual ~FungeState() = default;
		
		virtual bool execute(inst_t i) = 0;
	
	protected:
		FungeRunner& runner;
		StackStack& stack;
};

}
