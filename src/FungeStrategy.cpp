/**
 * @file FungeStrategy.cpp
 * Strategy for executing Funge commands.
 * @author Conlan Wesson
 */

#include "FungeStrategy.h"
#include "FungeRunner.h"

namespace Funge {

FungeStrategy::FungeStrategy(FungeRunner& r, std::initializer_list<inst_t> in) :
	runner(r),
	field(r.getField()),
	ip(r.getIP()),
	stack(r.getStack()),
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
