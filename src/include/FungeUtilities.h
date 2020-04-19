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
	size_t popVector(Stack& stack, Vector& vector);
	
	std::string popString(Stack& stack);
}
