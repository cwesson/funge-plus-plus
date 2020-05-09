/**
 * @file FungeStateNormal.h
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeState.h"
#include "FungeStrategy.h"
#include <map>
#include <stack>

namespace Funge {

class FungeStateNormal : public FungeState {
	public:
		FungeStateNormal(FungeRunner& r, Field& f, StackStack& s, InstructionPointer& i);
		virtual ~FungeStateNormal();
		
		virtual bool execute(inst_t i) override;
		
		FungeStateNormal(const FungeStateNormal&) = delete;
		FungeStateNormal& operator=(const FungeStateNormal&) = delete;
	
	protected:
		std::vector<FungeStrategy*> strategies;
		std::map<inst_t, std::stack<FungeStrategy*>> semantics;
		
		bool load(FungeStrategy* strategy);
};

}
