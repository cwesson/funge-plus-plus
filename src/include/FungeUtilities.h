/**
 * @file FungeUtilities.h
 * Functions to aid in other parts of Funge.
 * @author Conlan Wesson
 */

#pragma once

#include "Stack.h"
#include "Vector.h"

namespace Funge {
	size_t pushVector(Stack& stack, const Vector& vector);
	Vector popVector(Stack& stack);
	
	size_t pushString(Stack& stack, const std::string& str);
	std::string popString(Stack& stack);
}
