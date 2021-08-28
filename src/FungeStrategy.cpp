/**
 * @file FungeStrategy.cpp
 * Strategy for executing Funge commands.
 * @author Conlan Wesson
 */

#include "FungeStrategy.h"

namespace Funge {

FungeStrategy::FungeStrategy(Field& f, InstructionPointer& i, StackStack& s, FungeRunner& r, std::initializer_list<inst_t> in) :
	field(f),
	ip(i),
	stack(s),
	runner(r),
	rd(),
	gen(rd()),
	inst(in)
{
	
}

const std::vector<inst_t>& FungeStrategy::instructions() const{
	return inst;
}

stack_t FungeStrategy::random(stack_t min, stack_t max){
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

}
