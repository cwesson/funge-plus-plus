/**
 * @file FingerprintHRTI.h
 * High Resolution Timer Interface.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include "Vector.h"
#include <chrono>

namespace Funge {

class FingerprintHRTI : public Fingerprint {
	public:
		FingerprintHRTI(FungeRunner& r);
		virtual ~FingerprintHRTI() = default;
		
		virtual bool execute(inst_t cmd) override;
	
	protected:
		std::chrono::steady_clock::time_point hrti_mark;
};

}
