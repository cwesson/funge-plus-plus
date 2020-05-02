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
		FingerprintStrategy(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~FingerprintStrategy();
		
		virtual bool execute(inst_t cmd) override;
		
		bool load(uint64_t fingerprint);
		bool unload(uint64_t fingerprint);
	
	protected:
		std::map<uint64_t, Fingerprint*> available;
		std::map<inst_t, std::stack<Fingerprint*>> loaded;
};

}
