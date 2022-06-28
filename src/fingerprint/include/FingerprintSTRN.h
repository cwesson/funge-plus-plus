/**
 * @file FingerprintSTRN.h
 * String functions.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintSTRN : public Fingerprint {
	public:
		explicit FingerprintSTRN(FungeRunner& r);
		virtual ~FingerprintSTRN() = default;
		
		virtual FungeError execute(inst_t cmd) override;
};

}
