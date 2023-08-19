/**
 * @file FingerprintTRDS.h
 * IP travel in time and space.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintTRDS : public Fingerprint {
	public:
		explicit FingerprintTRDS(FungeRunner& r);
		virtual ~FingerprintTRDS() = default;
		
		virtual FungeError execute(inst_t cmd) override;
};

}
