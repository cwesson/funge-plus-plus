/**
 * @file Unefunge93Strategy.h
 * Strategy for Unefunge-93 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeStrategy.h"

namespace Funge {

class Unefunge93Strategy : public FungeStrategy {
	public:
		Unefunge93Strategy(FungeRunner& r);
		virtual ~Unefunge93Strategy() = default;
		
		virtual bool operator()(inst_t cmd) override;
		virtual FungeStrategy* clone(FungeRunner& r) const override;
	
	private:
		bool instructionStop(inst_t i);
};

}
