/**
 * @file FingerprintORTH.h
 * Orthogonal Easement Library.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintORTH : public Fingerprint {
	public:
		FingerprintORTH(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~FingerprintORTH() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
