/**
 * @file FingerprintStrategy.h
 * Strategy for fingerprint commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeStrategy.h"
#include "Fingerprint.h"
#include <map>
#include <stack>

namespace Funge {

class FingerprintStrategy : public FungeStrategy {
	public:
		explicit FingerprintStrategy(FungeRunner& r);
		FingerprintStrategy(const FingerprintStrategy& orig, FungeRunner& r);
		virtual ~FingerprintStrategy();
		virtual FungeStrategy* clone(FungeRunner& r) const override;
		
		bool load(uint64_t fingerprint);
		bool unload(uint64_t fingerprint);
	
	protected:
		FungeError execute(Fingerprint* fing, inst_t i);
		Fingerprint* loadBuiltin(uint64_t fingerprint);
		Fingerprint* loadFL(uint64_t fingerprint);

		std::string intToStr(uint64_t i);
		void activate(Fingerprint* fing);

		std::map<uint64_t, Fingerprint*> available;
		std::vector<uint64_t> loaded;
};

}
