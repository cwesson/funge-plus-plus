/**
 * @file StackStack.cpp
 * Stack of Stacks
 * @author Conlan Wesson
 */

#include "StackStack.h"

namespace Funge {

StackStack::StackStack(){
	stack.push_back(Stack());
}

Stack& StackStack::top(){
	return stack.back();
}

Stack& StackStack::second(){
	return stack[stack.size()-2];
}

Stack& StackStack::at(size_t x){
	return stack[x];
}

const Stack& StackStack::top() const{
	return stack.back();
}

const Stack& StackStack::second() const{
	return stack[stack.size()-2];
}

const Stack& StackStack::at(size_t x) const{
	return stack[stack.size()-x-1];
}

void StackStack::pop(){
	stack.pop_back();
}

void StackStack::push(){
	stack.push_back(Stack());
}

size_t StackStack::size() const{
	return stack.size();
}

}
