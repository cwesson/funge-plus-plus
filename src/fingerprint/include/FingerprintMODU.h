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
		FingerprintMODU(FungeRunner& r);
		virtual ~FingerprintMODU() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
