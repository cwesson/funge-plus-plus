/**
 * @file FingerprintFungeLib.h
 * Dynamic Funge.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include "FungeUniverse.h"

namespace Funge {

class FingerprintFungeLib : public Fingerprint {
	public:
		explicit FingerprintFungeLib(FungeRunner& r, std::istream& file, FungeConfig& cfg);
		virtual ~FingerprintFungeLib() = default;
		
		virtual bool execute(inst_t cmd) override;
	
	private:
		FungeUniverse* dynamic;
};

}
