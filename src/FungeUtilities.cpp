/**
 * @file FungeUtilities.cpp
 * Functions to aid in other parts of Funge.
 * @author Conlan Wesson
 */

#include "FungeUtilities.h"
#include "FungeConfig.h"
#include "FungeUniverse.h"
#include "Stack.h"

namespace Funge {

size_t pushVector(FungeRunner& runner, const Vector& vector, Stack* stack){
	if(stack == nullptr){
		stack = &runner.getStack().top();
	}
	size_t s = runner.getUniverse().dimensions();
	for(size_t i = 0; i < s; ++i){
		stack->push(vector[i]);
	}
	return s;
}

Vector popVector(FungeRunner& runner, Stack* stack){
	if(stack == nullptr){
		stack = &runner.getStack().top();
	}
	Vector v;
	size_t s = runner.getUniverse().dimensions();
	for(size_t i = s; i > 0; --i){
		v.set(i-1, stack->pop());
	}
	return v;
}

size_t pushString(Stack& stack, const std::string& str){
	size_t s = str.length();
	stack.push(0);
	for(size_t c = s; c > 0; --c){
		stack.push(str[c-1]);
	}
	return s+1;
}

std::string popString(Stack& stack){
	std::string ret;
	for(stack_t c = stack.pop(); c != 0; c = stack.pop()){
		ret.push_back(static_cast<char>(c));
	}
	return ret;
}

}
