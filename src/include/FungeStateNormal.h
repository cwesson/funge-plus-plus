/**
 * @file FungeStateNormal.h
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeState.h"
#include "FungeStrategy.h"
#include "FungeSemantic.h"
#include <map>
#include <stack>

namespace Funge {

class FungeStateNormal : public FungeState {
	public:
		explicit FungeStateNormal(FungeRunner& r);
		FungeStateNormal(const FungeStateNormal& orig, FungeRunner& r);
		virtual ~FungeStateNormal();
		
		virtual bool execute(inst_t i) override;

		void pushSemantic(inst_t i, semantic_t func);
		semantic_t popSemantic(inst_t i);
		semantic_t getSemantic(inst_t i);
		
		FungeStateNormal& operator=(const FungeStateNormal&) = delete;
		FungeStateNormal(const FungeStateNormal& orig) = delete;
	
	protected:
		std::vector<FungeStrategy*> strategies;
		std::map<inst_t, std::stack<semantic_t>> semantics;
		
		bool load(FungeStrategy* strategy);
};

}
