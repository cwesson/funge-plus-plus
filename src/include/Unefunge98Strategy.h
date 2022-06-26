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
		explicit Unefunge98Strategy(FungeRunner& r);
		virtual ~Unefunge98Strategy() = default;
		
		virtual FungeStrategy* clone(FungeRunner& r) const override;
	
	private:
		Unefunge98Strategy(const Unefunge98Strategy& orig, FungeRunner& r);
		void init();

		FungeError instructionPush(int n);
		FungeError instructionSysInfo();
		FungeError instructionNoop();
		// Flow Control
		FungeError instructionJumpOver();
		FungeError instructionJumpForward();
		FungeError instructionReflect();
		FungeError instructionAbsolute();
		FungeError instructionIterate();
		FungeError instructionQuit();
		FungeError instructionThread();
		// Stack Operations
		FungeError instructionClear();
		FungeError instructionUnder();
		FungeError instructionBegin();
		FungeError instructionEnd();
		// I/O
		FungeError instructionFileIn();
		FungeError instructionFileOut();
		FungeError instructionExecute();
		// Self-Modifying
		FungeError instructionFetch();
		FungeError instructionStore();
		// Fingerprints
		FungeError instructionLoad();
		FungeError instructionUnload();

		void pushSysInfo(int num);
		FingerprintStrategy finger;
};

}
