/**
 * @file FingerprintBOOL.h
 * Boolean operators.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintBOOL : public Fingerprint {
	public:
		FingerprintBOOL(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~FingerprintBOOL() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
