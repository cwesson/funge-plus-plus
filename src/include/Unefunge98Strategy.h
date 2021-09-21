/**
 * @file Unefunge98Strategy.h
 * Strategy for Unefunge-98 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeStrategy.h"
#include "FingerprintStrategy.h"

namespace Funge {

class Unefunge98Strategy : public FungeStrategy {
	public:
		Unefunge98Strategy(FungeRunner& r);
		virtual ~Unefunge98Strategy() = default;
		
		virtual FungeStrategy* clone(FungeRunner& r) const override;
	
	private:
		bool instructionPush(inst_t i, int n);
		bool instructionSysInfo(inst_t i);
		bool instructionNoop(inst_t i);
		// Flow Control
		bool instructionJumpOver(inst_t i);
		bool instructionJumpForward(inst_t i);
		bool instructionReflect(inst_t i);
		bool instructionAbsolute(inst_t i);
		bool instructionIterate(inst_t i);
		bool instructionQuit(inst_t i);
		bool instructionThread(inst_t i);
		// Stack Operations
		bool instructionClear(inst_t i);
		bool instructionUnder(inst_t i);
		bool instructionBegin(inst_t i);
		bool instructionEnd(inst_t i);
		// I/O
		bool instructionFileIn(inst_t i);
		bool instructionFileOut(inst_t i);
		bool instructionExecute(inst_t i);
		// Self-Modifying
		bool instructionFetch(inst_t i);
		bool instructionStore(inst_t i);
		// Fingerprints
		bool instructionLoad(inst_t i);
		bool instructionUnload(inst_t i);

		void pushSysInfo(int num);
		FingerprintStrategy finger;
};

}
