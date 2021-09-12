/**
 * @file FingerprintTOYS.h
 * Standard Toys.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include <random>

namespace Funge {

class FingerprintTOYS : public Fingerprint {
	public:
		FingerprintTOYS(FungeRunner& r);
		virtual ~FingerprintTOYS() = default;
		
		virtual bool execute(inst_t cmd) override;
		
	private:
		std::default_random_engine rd;
		std::mt19937 gen;
		std::uniform_int_distribution<stack_t> dis;
		
		void copySpace(const Vector& src, const Vector& sz, const Vector& dest, bool low, bool move);
		bool sizeToRange(Vector& size);
};

}
