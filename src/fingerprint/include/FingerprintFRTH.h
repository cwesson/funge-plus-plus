/**
 * @file FingerprintFRTH.h
 * Some common forth commands.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintFRTH : public Fingerprint {
	public:
		FingerprintFRTH(FungeRunner& r);
		virtual ~FingerprintFRTH() = default;
		
		virtual bool execute(inst_t cmd) override;
};

}
