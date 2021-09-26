/**
 * @file FingerprintSUBR.h
 * Subroutine extension.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintSUBR : public Fingerprint {
	public:
		explicit FingerprintSUBR(FungeRunner& r);
		virtual ~FingerprintSUBR() = default;
		
		virtual bool execute(inst_t cmd) override;
	private:
		bool offset;
};

}
