/**
 * @file FingerprintSUBR.h
 * Subroutine extension.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintSUBR : public Fingerprint {
	public:
		FingerprintSUBR(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~FingerprintSUBR() = default;
		
		virtual bool execute(inst_t cmd) override;
	private:
		bool offset;
};

}
