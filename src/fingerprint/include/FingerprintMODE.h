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
		explicit FingerprintMODE(FungeRunner& r);
		virtual ~FingerprintMODE() = default;
		
		virtual FungeError execute(inst_t cmd) override;
};

}
