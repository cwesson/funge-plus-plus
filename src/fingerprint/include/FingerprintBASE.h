/**
 * @file FingerprintBASE.h
 * I/O for numbers in other bases.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include <string>

namespace Funge {

class FingerprintBASE : public Fingerprint {
	public:
		FingerprintBASE(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~FingerprintBASE() = default;
		
		virtual bool execute(inst_t cmd) override;
	
	private:
		static char digit_map[32];
		void printNum(stack_t num, unsigned int base);
		void printBase(stack_t num, unsigned int base, bool low);
		stack_t readNum(unsigned int base);
		bool readBase(std::string str, stack_t* num, unsigned int base);
};

}
