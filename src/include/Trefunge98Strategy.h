/**
 * @file Trefunge98Strategy.h
 * Strategy for Trefunge-98 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeStrategy.h"

namespace Funge {

class Trefunge98Strategy : public FungeStrategy {
	public:
		explicit Trefunge98Strategy(FungeRunner& r);
		virtual ~Trefunge98Strategy() = default;
		
		virtual FungeStrategy* clone(FungeRunner& r) const override;

	private:
		bool instructionHigh();
		bool instructionLow();
		bool instructionIf();
};

}
