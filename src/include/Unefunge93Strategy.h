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
		bool instructionPush(inst_t i, int n);
		// Flow Control
		bool instructionWest(inst_t i);
		bool instructionEast(inst_t i);
		bool instructionStop(inst_t i);
		bool instructionTrampoline(inst_t i);
		bool instructionIf(inst_t i);
		bool instructionGoAway(inst_t i);
		// Arithmetic Operators
		bool instructionNot(inst_t i);
		bool instructionRemainder(inst_t i);
		bool instructionMultiply(inst_t i);
		bool instructionAdd(inst_t i);
		bool instructionSubtract(inst_t i);
		bool instructionDivide(inst_t i);
		bool instructionGreater(inst_t i);
		// Stack Operators
		bool instructionPop(inst_t i);
		bool instructionDuplicate(inst_t i);
		bool instructionSwap(inst_t i);
		// Input
		bool instructionNumIn(inst_t i);
		bool instructionCharIn(inst_t i);
		bool instructionString(inst_t i);
		// Output
		bool instructionNumOut(inst_t i);
		bool instructionCharOut(inst_t i);
		// Self-Modifying
		bool instructionGet(inst_t i);
		bool instructionPut(inst_t i);
};

}
