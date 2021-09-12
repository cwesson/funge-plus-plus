/**
 * @file FingerprintLONG.h
 * Long Integers.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include "bigint.h"

namespace Funge {

class FingerprintLONG : public Fingerprint {
	public:
		FingerprintLONG(FungeRunner& r);
		virtual ~FingerprintLONG() = default;
		
		virtual bool execute(inst_t cmd) override;

	private:
		typedef bigint<uint64_t> fungelong_t;
		static_assert(sizeof(fungelong_t) == sizeof(stack_t)*2);

		fungelong_t popLong();
		void pushLong(fungelong_t n);
};

}
