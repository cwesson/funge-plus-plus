/**
 * @file FingerprintROMA.h
 * Roman Numerals.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintROMA : public Fingerprint {
	public:
		FingerprintROMA(FungeRunner& r);
		virtual ~FingerprintROMA() = default;
		
		virtual bool execute(inst_t cmd) override;
	
	private:
		void print(stack_t n);

		static const std::string hundreds[9];
		static const std::string tens[9];
		static const std::string ones[9];
};

}
