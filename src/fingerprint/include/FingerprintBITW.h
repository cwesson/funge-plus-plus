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
		explicit FingerprintBITW(FungeRunner& r);
		virtual ~FingerprintBITW() = default;
		
		virtual FungeError execute(inst_t cmd) override;
};

}
