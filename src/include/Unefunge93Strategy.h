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
		explicit Unefunge93Strategy(FungeRunner& r);
		virtual ~Unefunge93Strategy() = default;
		
		virtual FungeStrategy* clone(FungeRunner& r) const override;
	
	private:
		FungeError instructionSkip();
		FungeError instructionPush(int n);
		// Flow Control
		FungeError instructionWest();
		FungeError instructionEast();
		FungeError instructionStop();
		FungeError instructionTrampoline();
		FungeError instructionIf();
		FungeError instructionGoAway();
		// Arithmetic Operators
		FungeError instructionNot();
		FungeError instructionRemainder();
		FungeError instructionMultiply();
		FungeError instructionAdd();
		FungeError instructionSubtract();
		FungeError instructionDivide();
		FungeError instructionGreater();
		// Stack Operators
		FungeError instructionPop();
		FungeError instructionDuplicate();
		FungeError instructionSwap();
		// Input
		FungeError instructionNumIn();
		FungeError instructionCharIn();
		FungeError instructionString();
		// Output
		FungeError instructionNumOut();
		FungeError instructionCharOut();
		// Self-Modifying
		FungeError instructionGet();
		FungeError instructionPut();

		void errorHandler(FungeError e);
};

}
