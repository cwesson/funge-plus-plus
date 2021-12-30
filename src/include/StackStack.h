/**
 * @file StackStack.h
 * Stack of Stacks
 * @author Conlan Wesson
 */

#pragma once

#include "Stack.h"
#include <vector>

namespace Funge {
class FungeRunner;

/**
 * Stack of stacks.
 */
class StackStack {
	public:
		/**
		 * Constructor.
		 * @param r Runner the StackStack belongs to.
		 */
		explicit StackStack(FungeRunner& r);

		/**
		 * Copy constructor.
		 */
		StackStack(const StackStack& orig) = delete;

		/**
		 * Copy constructor.
		 * @param orig Original StackStack.
		 * @param r Runner the new StackStack belongs to.
		 */
		StackStack(const StackStack& orig, FungeRunner& r);

		/**
		 * Get the top Stack.
		 * @return Top Stack.
		 */
		Stack& top();

		/**
		 * Get the second Stack.
		 * @return Second Stack.
		 */
		Stack& second();

		/**
		 * Get the Stack at position x.
		 * @param x Stack to get.
		 * @return Stack at position x.
		 */
		Stack& at(size_t x);

		/**
		 * Get the top Stack.
		 * @return Top Stack.
		 */
		const Stack& top() const;

		/**
		 * Get the second Stack.
		 * @return Second Stack.
		 */
		const Stack& second() const;

		/**
		 * Get the Stack at position x.
		 * @param x Stack to get.
		 * @return Stack at position x.
		 */
		const Stack& at(size_t x) const;
		
		/**
		 * Pop the top Stack.
		 */
		void pop();

		/**
		 * Push a new empty Stack.
		 */
		void push();

		/**
		 * Get the number of stacks.
		 * @return Number of stacks.
		 */
		size_t size() const;

		/**
		 * Get the runner.
		 * @return Runner the StackStack belongs to.
		 */
		FungeRunner& getRunner();
		
	private:
		FungeRunner& runner;
		std::vector<Stack> stack;
};

}
