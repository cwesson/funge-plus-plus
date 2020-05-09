/**
 * @file FungeStrategy.cpp
 * Strategy for executing Funge commands.
 * @author Conlan Wesson
 */

#include "FungeStrategy.h"

namespace Funge {

FungeStrategy::FungeStrategy(Field& f, InstructionPointer& i, StackStack& s, FungeState& t, std::initializer_list<inst_t> in) :
	field(f),
	ip(i),
	stack(s),
	state(t),
	rd(),
	gen(rd()),
	dis(),
	inst(in)
{
	
}

const std::vector<inst_t>& FungeStrategy::instructions() const{
	return inst;
}

stack_t FungeStrategy::random(){
	return dis(gen);
}

}
