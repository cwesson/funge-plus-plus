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
		Unefunge98Strategy(const Unefunge98Strategy& orig, FungeRunner& r);
		void init();

		bool instructionPush(int n);
		bool instructionSysInfo();
		bool instructionNoop();
		// Flow Control
		bool instructionJumpOver();
		bool instructionJumpForward();
		bool instructionReflect();
		bool instructionAbsolute();
		bool instructionIterate();
		bool instructionQuit();
		bool instructionThread();
		// Stack Operations
		bool instructionClear();
		bool instructionUnder();
		bool instructionBegin();
		bool instructionEnd();
		// I/O
		bool instructionFileIn();
		bool instructionFileOut();
		bool instructionExecute();
		// Self-Modifying
		bool instructionFetch();
		bool instructionStore();
		// Fingerprints
		bool instructionLoad();
		bool instructionUnload();

		void pushSysInfo(int num);
		FingerprintStrategy finger;
};

}
