/**
 * @file FingerprintNULL.h
 * Null Fingerprint.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintNULL : public Fingerprint {
	public:
		FingerprintNULL(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~FingerprintNULL() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
