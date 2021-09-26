/**
 * @file FingerprintTERM.h
 * Terminal extension.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include <string>

namespace Funge {

class FingerprintTERM : public Fingerprint {
	public:
		explicit FingerprintTERM(FungeRunner& r);
		virtual ~FingerprintTERM() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
