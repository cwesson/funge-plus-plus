/**
 * @file Fingerprint.h
 * Fingerprint template.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeRunner.h"
#include "funge_types.h"

namespace Funge {

class Fingerprint {
	public:
		Fingerprint(FungeRunner& r, std::initializer_list<inst_t> in);
		virtual ~Fingerprint() = default;
		
		virtual bool execute(inst_t cmd) = 0;

		virtual void activate(){}
		
		const std::vector<inst_t>& instructions() const;
	
	protected:
		Field& field;
		InstructionPointer& ip;
		StackStack& stack;
	
	private:
		std::vector<inst_t> inst;
};

}
