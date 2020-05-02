/**
 * @file FingerprintBITW.h
 * Bitwise operators.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintBITW : public Fingerprint {
	public:
		FingerprintBITW(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~FingerprintBITW() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
