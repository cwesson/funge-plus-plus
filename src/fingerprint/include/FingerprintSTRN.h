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
		FingerprintSTRN(FungeRunner& r);
		virtual ~FingerprintSTRN() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
