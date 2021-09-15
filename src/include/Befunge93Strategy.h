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
		
		virtual bool execute(inst_t cmd) override;
		virtual FungeStrategy* clone(FungeRunner& r) const override;
};

}
