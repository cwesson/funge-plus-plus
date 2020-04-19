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
		
		void pop();
		void push();
		
		size_t size();
		
	private:
		std::vector<Stack> stack;
};

}
