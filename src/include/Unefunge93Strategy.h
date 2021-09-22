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
		
		virtual FungeStrategy* clone(FungeRunner& r) const override;
	
	private:
		bool instructionPush(int n);
		// Flow Control
		bool instructionWest();
		bool instructionEast();
		bool instructionStop();
		bool instructionTrampoline();
		bool instructionIf();
		bool instructionGoAway();
		// Arithmetic Operators
		bool instructionNot();
		bool instructionRemainder();
		bool instructionMultiply();
		bool instructionAdd();
		bool instructionSubtract();
		bool instructionDivide();
		bool instructionGreater();
		// Stack Operators
		bool instructionPop();
		bool instructionDuplicate();
		bool instructionSwap();
		// Input
		bool instructionNumIn();
		bool instructionCharIn();
		bool instructionString();
		// Output
		bool instructionNumOut();
		bool instructionCharOut();
		// Self-Modifying
		bool instructionGet();
		bool instructionPut();
};

}
