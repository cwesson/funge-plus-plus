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
		explicit Befunge98Strategy(FungeRunner& r);
		virtual ~Befunge98Strategy() = default;
		
		virtual FungeStrategy* clone(FungeRunner& r) const override;

	private:
		FungeError instructionLeft();
		FungeError instructionRight();
		FungeError instructionCompare();
};

}
