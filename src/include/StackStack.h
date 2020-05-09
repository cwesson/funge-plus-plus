/**
 * @file StackStack.h
 * Stack of Stacks
 * @author Conlan Wesson
 */

#pragma once

#include <vector>
#include "Stack.h"

namespace Funge {

class StackStack {
	public:
		StackStack();
		
		Stack& top();
		Stack& second();
		Stack& at(size_t x);
		
		const Stack& top() const;
		const Stack& second() const;
		const Stack& at(size_t x) const;
		
		void pop();
		void push();
		
		size_t size() const;
		
	private:
		std::vector<Stack> stack;
};

}
