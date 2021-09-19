/**
 * @file FungeStateNormal.h
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeState.h"
#include "FungeStrategy.h"
#include <functional>
#include <map>
#include <stack>

namespace Funge {

class FungeStateNormal : public FungeState {
	public:
		FungeStateNormal(FungeRunner& r);
		FungeStateNormal(const FungeStateNormal& orig, FungeRunner& r);
		virtual ~FungeStateNormal();
		
		virtual bool execute(inst_t i) override;
		
		FungeStateNormal& operator=(const FungeStateNormal&) = delete;
		FungeStateNormal(const FungeStateNormal& orig) = delete;
	
	protected:
		std::vector<FungeStrategy*> strategies;
		std::map<inst_t, std::stack<FungeStrategy*>> semantics;
		
		bool load(FungeStrategy* strategy);
};

}
