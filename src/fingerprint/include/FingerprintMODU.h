/**
 * @file FingerprintMODU.h
 * Modulo Arithmetic Extension.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintMODU : public Fingerprint {
	public:
		explicit FingerprintMODU(FungeRunner& r);
		virtual ~FingerprintMODU() = default;
		
		virtual FungeError execute(inst_t cmd) override;
};

}
