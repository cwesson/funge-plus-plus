/**
 * @file FingerprintJSTR.h
 * 3d string vectors.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include "FungeDebugger.h"

namespace Funge {

class FingerprintJSTR : public Fingerprint {
	public:
		explicit FingerprintJSTR(FungeRunner& r);
		virtual ~FingerprintJSTR() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
