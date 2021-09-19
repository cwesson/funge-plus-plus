/**
 * @file Unefunge98Strategy.h
 * Strategy for Unefunge-98 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeStrategy.h"
#include "FingerprintStrategy.h"

namespace Funge {

class Unefunge98Strategy : public FungeStrategy {
	public:
		Unefunge98Strategy(FungeRunner& r);
		virtual ~Unefunge98Strategy() = default;
		
		virtual bool operator()(inst_t cmd) override;
		virtual FungeStrategy* clone(FungeRunner& r) const override;
	
	private:
		void pushSysInfo(int num);
		FingerprintStrategy finger;
};

}
