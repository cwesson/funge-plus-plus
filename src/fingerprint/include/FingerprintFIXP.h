/**
 * @file FingerprintFIXP.h
 * Fixed point math functions.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include <random>

namespace Funge {

class FingerprintFIXP : public Fingerprint {
	public:
		FingerprintFIXP(FungeRunner& r);
		virtual ~FingerprintFIXP() = default;
		
		virtual bool execute(inst_t cmd) override;

	private:
		std::default_random_engine rd;
		std::mt19937 gen;

		double stackToFloat(stack_t n);
		stack_t floatToStack(double n);
		double degToRad(double deg);
		double radToDeg(double deg);
		stack_t random(stack_t max);
};

}
