/**
 * @file FingerprintMODE.h
 * Standard Modes.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintMODE : public Fingerprint {
	public:
		FingerprintMODE(FungeRunner& r);
		virtual ~FingerprintMODE() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
