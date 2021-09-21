/**
 * @file Befunge93Strategy.h
 * Strategy for Befunge-93 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeStrategy.h"

namespace Funge {

class Befunge93Strategy : public FungeStrategy {
	public:
		Befunge93Strategy(FungeRunner& r);
		virtual ~Befunge93Strategy() = default;
		
		virtual FungeStrategy* clone(FungeRunner& r) const override;

	private:
		bool instructionNorth(inst_t i);
		bool instructionSouth(inst_t i);
		bool instructionIf(inst_t i);
};

}
