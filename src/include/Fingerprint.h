/**
 * @file Fingerprint.h
 * Fingerprint template.
 * @author Conlan Wesson
 */

#pragma once

#include "Field.h"
#include "InstructionPointer.h"
#include "StackStack.h"
#include "funge_types.h"

namespace Funge {

class Fingerprint {
	public:
		Fingerprint(Field& f, InstructionPointer& i, StackStack& s, std::initializer_list<inst_t> in) :
			field(f), ip(i), stack(s), inst(in) {}
		virtual ~Fingerprint() = default;
		
		virtual bool execute(inst_t cmd) = 0;
		
		const std::vector<inst_t>& instructions() const{
			return inst;
		}
	
	protected:
		Field& field;
		InstructionPointer& ip;
		StackStack& stack;
		
		std::vector<inst_t> inst;
};

}
