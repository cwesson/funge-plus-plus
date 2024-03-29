/**
 * @file FingerprintDBUG.h
 * Software debugging.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include "FungeDebugger.h"

namespace Funge {

class FingerprintDBUG : public Fingerprint {
	public:
		explicit FingerprintDBUG(FungeRunner& r);
		FingerprintDBUG(const FingerprintDBUG& orig) = delete;
		FingerprintDBUG operator=(const FingerprintDBUG& orig) = delete;
		virtual ~FingerprintDBUG() = default;
		
		virtual FungeError execute(inst_t cmd) override;

		virtual void activate() override;
	
	private:
		FungeDebugger* dbg;
};

}
