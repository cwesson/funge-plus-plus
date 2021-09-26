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
		explicit FingerprintBASE(FungeRunner& r);
		virtual ~FingerprintBASE() = default;
		
		virtual bool execute(inst_t cmd) override;
	
	private:
		static const char digit_map[32];
		static const char base36[36];
		static const char base58[58];
		static const char base64[64];
		static const char base85[85];
		
		std::map<unsigned int, const char*> base_map;
		
		void printNum(stack_t num, unsigned int base) const;
		void printBase(stack_t num, unsigned int base, bool low) const;
		stack_t readNum(unsigned int base) const;
		bool readBase(std::string str, stack_t* num, unsigned int base) const;
};

}
