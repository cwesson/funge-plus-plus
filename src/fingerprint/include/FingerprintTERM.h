/**
 * @file FingerprintTERM.h
 * Terminal extension.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include <string>

namespace Funge {

class FingerprintTERM : public Fingerprint {
	public:
		FingerprintTERM(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~FingerprintTERM() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
