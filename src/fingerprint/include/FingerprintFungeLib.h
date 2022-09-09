/**
 * @file FingerprintFungeLib.h
 * Dynamic Funge.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include "FungeUniverse.h"
#include <string>

namespace Funge {

class FingerprintFungeLib : public Fingerprint {
	public:
		explicit FingerprintFungeLib(FungeRunner& r, std::istream& file, FungeConfig& cfg);
		FingerprintFungeLib(const FingerprintFungeLib& orig) = delete;
		FingerprintFungeLib operator=(const FingerprintFungeLib& orig) = delete;
		virtual ~FingerprintFungeLib() = default;

		static FingerprintFungeLib* factory(FungeRunner& r, const std::string& name);
		
		virtual FungeError execute(inst_t cmd) override;
	
	private:
		FungeUniverse* dynamic;
};

}
