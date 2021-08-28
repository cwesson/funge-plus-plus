/**
 * @file FingerprintFPRT.h
 * Formatted print.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintFPRT : public Fingerprint {
	public:
		FingerprintFPRT(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~FingerprintFPRT() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
