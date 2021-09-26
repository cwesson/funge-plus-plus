/**
 * @file FingerprintPERL.h
 * Generic Interface to the Perl Language.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include <string>

namespace Funge {

class FingerprintPERL : public Fingerprint {
	public:
		explicit FingerprintPERL(FungeRunner& r);
		virtual ~FingerprintPERL() = default;
		
		virtual bool execute(inst_t cmd) override;
	
	private:
		int perl(const std::string&);
};

}
