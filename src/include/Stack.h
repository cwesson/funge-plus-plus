/**
 * @file Stack.h
 * Wrapper around Java Stack in order to handle Befunge style stacks.
 * @author Conlan Wesson
 */

#pragma once

#include <cstddef>
#include <list>
#include "funge_types.h"

namespace Funge {
class StackStack;

class Stack {
	public:
		Stack(StackStack& s);
		//Stack(const Stack& orig) = delete;
		Stack(const Stack& orig, StackStack& s);
		
		stack_t pop();
		stack_t peek() const;
		size_t push(stack_t v);
		void clear();
		
		size_t size() const;
		
		stack_t get(size_t p) const;
		stack_t operator[](size_t p) const;
	
	private:
		StackStack& ss;
		std::list<stack_t> stack;
};

}
