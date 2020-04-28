/**
 * @file Stack.h
 * Wrapper around Java Stack in order to handle Befunge style stacks.
 * @author Conlan Wesson
 */

#pragma once

#include <vector>
#include "funge_types.h"

namespace Funge {

class Stack {
	public:
		Stack();
		
		stack_t pop();
		stack_t peek();
		size_t push(stack_t v);
		void clear();
		
		size_t size();
		
		stack_t get(size_t p) const;
		stack_t operator[](size_t p) const;
	
	private:
		std::vector<stack_t> stack;
};

}
