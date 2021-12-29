/**
 * @file StackStack.h
 * Stack of Stacks
 * @author Conlan Wesson
 */

#pragma once

#include <vector>
#include "Stack.h"

namespace Funge {
class FungeRunner;

class StackStack {
	public:
		StackStack(FungeRunner& r);
		StackStack(const StackStack& orig) = delete;
		StackStack(const StackStack& orig, FungeRunner& r);
		
		Stack& top();
		Stack& second();
		Stack& at(size_t x);
		
		const Stack& top() const;
		const Stack& second() const;
		const Stack& at(size_t x) const;
		
		void pop();
		void push();
		
		size_t size() const;

		FungeRunner& getRunner();
		
	private:
		FungeRunner& runner;
		std::vector<Stack> stack;
};

}
