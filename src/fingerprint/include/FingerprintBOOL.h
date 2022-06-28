/**
 * @file FingerprintBOOL.h
 * Boolean operators.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintBOOL : public Fingerprint {
	public:
		explicit FingerprintBOOL(FungeRunner& r);
		virtual ~FingerprintBOOL() = default;
		
		virtual FungeError execute(inst_t cmd) override;
};

}
