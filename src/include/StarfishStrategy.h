/**
 * @file StarfishStrategy.h
 * Strategy for *><> commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FishStrategy.h"
#include <stack>

namespace Funge {

class StarfishStrategy : public FishStrategy {
	public:
		explicit StarfishStrategy(FungeRunner& r);
		virtual ~StarfishStrategy() = default;
	
	private:
		// Movement
		FungeError instructionFisherman();
		FungeError instructionCall();
		FungeError instructionReturn();
		FungeError instructionDive();
		FungeError instructionRise();
		// Arithmetic
		FungeError instructionIncrement();
		FungeError instructionDecrement();
		// I/O
		FungeError instructionFile();
		// Miscellaneous
		FungeError instructionSleep();
		FungeError instructionHour();
		FungeError instructionMinute();
		FungeError instructionSecond();

		enum {
			FISHER_UP,
			FISHER_DOWN,
		} fisherstate;

		Vector fishercache;

};

}
