/**
 * @file Stack.h
 * Wrapper around Java Stack in order to handle Befunge style stacks.
 * @author Conlan Wesson
 */

#pragma once

#include <stack>
#include "funge_types.h"

namespace Funge {

class Stack {
	public:
		Stack();
		
		stack_t pop();
		stack_t peek();
		void push(stack_t v);
		void clear();
		
		size_t size();
	
	private:
		std::stack<stack_t> stack;
};

}
