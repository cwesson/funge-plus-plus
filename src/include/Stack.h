/**
 * @file Stack.h
 * Wrapper around list in order to handle Befunge style stacks.
 * @author Conlan Wesson
 */

#pragma once

#include "funge_types.h"
#include <cstddef>
#include <list>
#include <mutex>
#include <ostream>

namespace Funge {
class StackStack;

class Stack {
	public:
		/**
		 * Constructor.
		 */
		explicit Stack();

		/**
		 * Copy constructor.
		 * @param orig Original Stack.
		 */
		Stack(const Stack& orig);

		/**
		 * Copy constructor.
		 */
		Stack(const Stack&& orig) = delete;

		/**
		 * Remove the top value on the stack.
		 * @return Top value.
		 * @retval 0 when stack is empty.
		 */
		stack_t pop();

		/**
		 * Check the top value on the stack.
		 * @return Top value.
		 */
		stack_t peek() const;

		/**
		 * Push to the stack.
		 * @param v Value to push.
		 * @return Number of items pushed.
		 */
		size_t push(stack_t v);

		/**
		 * Remove all items from the stack.
		 */
		void clear();

		/**
		 * Get the number of items on the stack.
		 * @return Number of items.
		 */
		size_t size() const;

		/**
		 * Get the number of push/pop operations performed on the stack.
		 * @return Number of operations.
		 */
		size_t age() const;

		/**
		 * Get a value from the stack.
		 * @param p Position, 1 is top of the stack.
		 * @return Item at position p.
		 * @retval 0 when p is 0 or stack size is less than p.
		 */
		stack_t get(size_t p) const;
		stack_t operator[](size_t p) const;

		/**
		 * Set stack mode
		 * @param m Stack mode.
		 * @note FUNGE_MODE_QUEUE pops from the bottom of the stack.
		 * @note FUNGE_MODE_INVERT pushes to the bottom of the stack.
		 */
		void setMode(FungeMode m);

		/**
		 * Output stream operator.
		 */
		friend std::ostream& operator<<(std::ostream& os, const Stack& rhs);
	
	private:
		FungeMode mode;
		std::list<stack_t> stack;
		size_t ops;
		mutable std::mutex mutex;
};

}
