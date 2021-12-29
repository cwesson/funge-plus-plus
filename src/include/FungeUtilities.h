/**
 * @file FungeUtilities.h
 * Functions to aid in other parts of Funge.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeRunner.h"
#include "Stack.h"
#include "Vector.h"

namespace Funge {
	size_t pushVector(FungeRunner& runner, const Vector& vector, Stack* stack=nullptr);
	Vector popVector(FungeRunner& runner, Stack* stack=nullptr);
	
	size_t pushString(Stack& stack, const std::string& str);
	std::string popString(Stack& stack);
}
