/**
 * @file FingerprintDynamic.h
 * Dynamic Funge.
 * @author Conlan Wesson
 */
#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintDynamic : public Fingerprint {
	public:
		explicit FingerprintDynamic(FungeRunner& r, FungeRunner* c);
		virtual ~FingerprintDynamic() = default;
		
		virtual FungeError execute(inst_t cmd) override;

		static constexpr uint64_t ID = 0x64796E616D696366;  // "dynamicf";
	
	private:
		FungeRunner* caller;
};

}
