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

		void setSemantic(inst_t i, std::function<bool(inst_t)> func);
		void popSemantic(inst_t i);
		
		FungeStateNormal& operator=(const FungeStateNormal&) = delete;
		FungeStateNormal(const FungeStateNormal& orig) = delete;
	
	protected:
		std::vector<FungeStrategy*> strategies;
		std::map<inst_t, std::stack<std::function<bool(inst_t)>>> semantics;
		
		bool load(FungeStrategy* strategy);
};

}
