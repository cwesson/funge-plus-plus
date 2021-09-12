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
		FingerprintBITW(FungeRunner& r);
		virtual ~FingerprintBITW() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
