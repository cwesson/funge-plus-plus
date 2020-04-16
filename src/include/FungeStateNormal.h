/**
 * @file FungeStateNormal.h
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeState.h"
#include "FungeStrategy.h"

namespace Funge {

class FungeStateNormal : public FungeState {
	public:
		FungeStateNormal(FungeRunner& r, StackStack& s, FungeStrategy* strat);
		virtual ~FungeStateNormal() = default;
		
		virtual bool execute(inst_t i);
	
	protected:
		FungeStrategy* strategy;
};

}
