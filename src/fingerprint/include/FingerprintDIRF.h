/**
 * @file FingerprintDIRF.h
 * Directory functions.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintDIRF : public Fingerprint {
	public:
		explicit FingerprintDIRF(FungeRunner& r);
		virtual ~FingerprintDIRF() = default;
		
		virtual FungeError execute(inst_t cmd) override;
};

}
