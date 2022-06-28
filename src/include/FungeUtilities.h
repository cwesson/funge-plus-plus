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

/**
 * Push a Vector to a Stack.
 * @param runner Runner requesting push.
 * @param vector Vector to push.
 * @param stack Stack to push to, default is top stack.
 */
size_t pushVector(FungeRunner& runner, const Vector& vector, Stack* stack=nullptr);

/**
 * Pop a Vector from a Stack.
 * @param runner Runner requesting pop.
 * @param stack Stack to pop from, default is top stack.
 * @return Vector poped.
 */
Vector popVector(FungeRunner& runner, Stack* stack=nullptr);

/**
 * Pop a Vector from a Stack.
 * @param runner Runner requesting pop.
 * @param size Size of vector.
 * @param stack Stack to pop from, default is top stack.
 * @return Vector poped.
 */
Vector popVector(FungeRunner& runner, size_t size, Stack* stack=nullptr);

/**
 * Push a string to a Stack.
 * @param stack Stack to push to.
 * @param str String to push.
 * @return Number of characters pushed.
 */
size_t pushString(Stack& stack, const std::string& str);

/**
 * Pop a string from a Stack.
 * @param stack Stack to pop from.
 * @return String poped.
 */
std::string popString(Stack& stack);

}
