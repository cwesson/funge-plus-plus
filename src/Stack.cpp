/**
 * @file Stack.cpp
 * Wrapper around Java Stack in order to handle Befunge style stacks.
 * @author Conlan Wesson
 */

#include "Stack.h"

namespace Funge {

Stack::Stack(){
	
}

stack_t Stack::pop(){
	stack_t ret = 0;
	if(!stack.empty()){
		ret = stack.top();
		stack.pop();
	}
	return ret;
}

stack_t Stack::peek(){
	stack_t ret = 0;
	if(!stack.empty()){
		ret = stack.top();
	}
	return ret;
}

size_t Stack::push(stack_t v){
	stack.push(v);
	return 1;
}

void Stack::clear(){
	while(!stack.empty()){
		stack.pop();
	}
}

size_t Stack::size(){
	return stack.size();
}

}
