/**
 * @file Befunge98Strategy.h
 * Strategy for Befunge-98 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeStrategy.h"

namespace Funge {

class Befunge98Strategy : public FungeStrategy {
	public:
		Befunge98Strategy(FungeRunner& r);
		virtual ~Befunge98Strategy() = default;
		
		virtual bool operator()(inst_t cmd) override;
		virtual FungeStrategy* clone(FungeRunner& r) const override;
};

}
