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
		FingerprintROMA(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~FingerprintROMA() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
