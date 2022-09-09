/**
 * @file FungeStrategy.cpp
 * Strategy for executing Funge commands.
 * @author Conlan Wesson
 */

#include "FungeStrategy.h"
#include "FungeRunner.h"

namespace Funge {

FungeStrategy::FungeStrategy(FungeRunner& r) :
	runner(r),
	field(r.getField()),
	ip(r.getIP()),
	stack(r.getStack()),
	rd(),
	gen(rd())
{
	
}

stack_t FungeStrategy::random(stack_t min, stack_t max){
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

FungeError FungeStrategy::push(stack_t n){
	stack.top().push(n);
	return ERROR_NONE;
}

}
