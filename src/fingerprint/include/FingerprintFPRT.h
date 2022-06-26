/**
 * @file FingerprintFPRT.h
 * Formatted print.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintFPRT : public Fingerprint {
	public:
		explicit FingerprintFPRT(FungeRunner& r);
		virtual ~FingerprintFPRT() = default;
		
		virtual FungeError execute(inst_t cmd) override;
};

}
