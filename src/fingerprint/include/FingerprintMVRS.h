/**
 * @file FingerprintMVRS.h
 * Multiverse extension.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintMVRS : public Fingerprint {
	public:
		explicit FingerprintMVRS(FungeRunner& r);
		virtual ~FingerprintMVRS() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
