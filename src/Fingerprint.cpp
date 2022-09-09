/**
 * @file Fingerprint.cpp
 * Fingerprint template.
 * @author Conlan Wesson
 */

#include "Fingerprint.h"
#include "InstructionPointer.h"
#include "StackStack.h"
#include "funge_types.h"

namespace Funge {

Fingerprint::Fingerprint(FungeRunner& r, std::initializer_list<inst_t> in) :
	runner(r),
	field(r.getField()),
	ip(r.getIP()),
	stack(r.getStack()),
	inst(in)
{}

const std::vector<inst_t>& Fingerprint::instructions() const{
	return inst;
}

void Fingerprint::activate(){
	for(auto i : inst){
		runner.pushSemantic(i, std::bind(&Fingerprint::execute, this, i));
	}
}

}
