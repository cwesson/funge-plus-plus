/**
 * @file FingerprintIIPC.h
 * Inter-IP Communication.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintIIPC : public Fingerprint {
	public:
		explicit FingerprintIIPC(FungeRunner& r);
		virtual ~FingerprintIIPC() = default;
		
		virtual FungeError execute(inst_t cmd) override;
	
	private:
		size_t sage;
		bool dormant;
};

}
