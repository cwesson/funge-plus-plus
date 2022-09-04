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
		FungeStateNormal(const FungeStateNormal& orig) = delete;
		virtual ~FungeStateNormal() = default;
		
		virtual FungeError execute(inst_t i) override;

		void pushSemantic(inst_t i, FungeSemantic* func);
		FungeSemantic* popSemantic(inst_t i);
		FungeSemantic* getSemantic(inst_t i);
		
		FungeStateNormal& operator=(const FungeStateNormal&) = delete;
	
	protected:
		std::map<inst_t, std::stack<FungeSemantic*>> semantics;
};

}
