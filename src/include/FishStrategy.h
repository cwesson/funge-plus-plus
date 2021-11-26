/**
 * @file FishStrategy.h
 * Strategy for ><> commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeStrategy.h"
#include <stack>

namespace Funge {

class FishStrategy : public FungeStrategy {
	public:
		explicit FishStrategy(FungeRunner& r);
		virtual ~FishStrategy() = default;
		
		virtual FungeStrategy* clone(FungeRunner& r) const override;
	
	private:
		bool instructionPush(stack_t n);
		// Directions
		bool instructionRight();
		bool instructionLeft();
		bool instructionDown();
		bool instructionUp();
		// Mirrors
		bool instructionMirror1();
		bool instructionMirror2();
		bool instructionMirrorVert();
		bool instructionMirrorHori();
		bool instructionMirrorAll();
		// Movement
		bool instructionRandom();
		bool instructionTrampoline();
		bool instructionConditional();
		bool instructionJump();
		// Arithmetic
		bool instructionAdd();
		bool instructionSub();
		bool instructionMult();
		bool instructionDiv();
		bool instructionModu();
		// Comparisons
		bool instructionEqual();
		bool instructionGreater();
		bool instructionLess();
		// Strings
		bool instructionString(inst_t i);
		// Stack Manipulation
		bool instructionDuplicate();
		bool instructionRemove();
		bool instructionSwap2();
		bool instructionSwap3();
		bool instructionLength();
		bool instructionShiftLeft();
		bool instructionShiftRight();
		bool instructionReverse();
		bool instructionCreateStack();
		bool instructionRemoveStack();
		// I/O
		bool instructionOutChar();
		bool instructionOutInt();
		bool instructionIn();
		// Miscellaneous
		bool instructionRegister();
		bool instructionGet();
		bool instructionPut();
		bool instructionEnd();

		struct reg {
			bool set;
			stack_t value;
		};

		std::stack<reg> regs;
};

}
