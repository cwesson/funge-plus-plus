/**
 * @file FingerprintStrategy.h
 * Strategy for fingerprint commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeStrategy.h"
#include <functional>

namespace Funge {

class FingerprintStrategy : public FungeStrategy {
	public:
		FingerprintStrategy(Field& f, InstructionPointer& i, StackStack& s);
		virtual ~FingerprintStrategy() = default;
		
		virtual bool execute(inst_t cmd) override;
		
		bool load(uint64_t fingerprint);
		bool unload(uint64_t fingerprint);
	
	protected:
		std::map<uint64_t, std::function<bool(inst_t)>> available;
		std::vector<uint64_t> loaded;
		
		bool execute_null(inst_t cmd);
		bool execute_orth(inst_t cmd);
		bool execute_refc(inst_t cmd);
		bool execute_roma(inst_t cmd);
};

}
