/**
 * @file StackStack.h
 * Stack of Stacks
 * @author Conlan Wesson
 */

#pragma once

#include "Stack.h"
#include "funge_types.h"
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
		 */
		explicit StackStack();

		/**
		 * Copy constructor.
		 * @param orig Original StackStack.
		 */
		StackStack(const StackStack& orig);

		/**
		 * Copy constructor.
		 */
		StackStack(const StackStack&& orig) = delete;

		/**
		 * Destructor.
		 */
		~StackStack();

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
		 * Insert a new empty Stack.
		 * @param pos Position to insert at.
		 */
		void insert(size_t pos);

		/**
		 * Remove a Stack.
		 * @param pos Position to remove.
		 */
		void remove(size_t pos);

		/**
		 * Get the number of stacks.
		 * @return Number of stacks.
		 */
		size_t size() const;

		/**
		 * Set the stack mode.
		 * @param m New mode.
		 */
		void setMode(FungeMode m);
		
	private:
		std::vector<Stack*> stack;
};

}
