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
		ret = stack.back();
		stack.pop_back();
	}
	return ret;
}

stack_t Stack::peek() const{
	stack_t ret = 0;
	if(!stack.empty()){
		ret = stack.back();
	}
	return ret;
}

size_t Stack::push(stack_t v){
	stack.push_back(v);
	return 1;
}

void Stack::clear(){
	stack.clear();
}

size_t Stack::size() const{
	return stack.size();
}

stack_t Stack::get(size_t p) const{
	if(p <= stack.size()){
		return stack[stack.size()-p];
	}
	return 0;
}

stack_t Stack::operator[](size_t p) const{
	return this->get(p);
}

}
