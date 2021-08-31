/**
 * @file FingerprintJSTR.h
 * 3d string vectors.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include "FungeDebugger.h"

namespace Funge {

class FingerprintJSTR : public Fingerprint {
	public:
		FingerprintJSTR(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~FingerprintJSTR() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
