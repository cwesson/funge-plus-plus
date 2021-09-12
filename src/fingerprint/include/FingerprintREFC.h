/**
 * @file FingerprintREFC.h
 * Referenced Cells Extension.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include "Vector.h"
#include <map>

namespace Funge {

class FingerprintREFC : public Fingerprint {
	public:
		FingerprintREFC(FungeRunner& r);
		virtual ~FingerprintREFC() = default;
		
		virtual bool execute(inst_t cmd) override;
	
	protected:
		static std::map<stack_t, Vector> refc_map;
};

}
