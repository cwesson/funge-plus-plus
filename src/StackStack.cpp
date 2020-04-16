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

Stack& StackStack::pop(){
	Stack& ret = stack.back();
	stack.pop_back();
	return ret;
}

void StackStack::push(Stack& s){
	stack.push_back(s);
}

size_t StackStack::size(){
	return stack.size();
}

}
