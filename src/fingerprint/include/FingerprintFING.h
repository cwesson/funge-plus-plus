/**
 * @file FingerprintFING.h
 * Operate on single fingerprint semantics.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintFING : public Fingerprint {
	public:
		explicit FingerprintFING(FungeRunner& r);
		virtual ~FingerprintFING() = default;
		
		virtual bool execute(inst_t cmd) override;
	
	private:
		bool instructionReflect();
};

}
