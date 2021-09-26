/**
 * @file FingerprintNFUN.h
 * N-Dimensional Funge.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintNFUN : public Fingerprint {
	public:
		explicit FingerprintNFUN(FungeRunner& r);
		virtual ~FingerprintNFUN() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
