/**
 * @file FungeUtilities.cpp
 * Functions to aid in other parts of Funge.
 * @author Conlan Wesson
 */

#include "FungeUtilities.h"
#include "FungeConfig.h"

namespace Funge {

size_t pushVector(Stack& stack, const Vector& vector){
	size_t s = funge_config.dimensions;
	for(size_t i = 0; i < s; ++i){
		stack.push(vector[i]);
	}
	return s;
}

size_t popVector(Stack& stack, Vector& vector){
	size_t s = funge_config.dimensions;
	for(size_t i = s; i > 0; --i){
		vector.set(i-1, stack.pop());
	}
	return s;
}

std::string popString(Stack& stack){
	std::string ret;
	for(stack_t c = stack.pop(); c != 0; c= stack.pop()){
		ret.push_back(static_cast<char>(c));
	}
	return ret;
}

}
