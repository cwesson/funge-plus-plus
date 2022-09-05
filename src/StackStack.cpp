/**
 * @file StackStack.cpp
 * Stack of Stacks
 * @author Conlan Wesson
 */

#include "StackStack.h"

namespace Funge {

StackStack::StackStack() :
	select(0),
	stack()
{
	stack.push_back(new Stack());
}

StackStack::~StackStack()
{
	while(stack.size() > 0){
		pop();
	}
}

StackStack::StackStack(const StackStack& orig) :
	select(orig.select),
	stack()
{
	for(size_t i = 0; i < orig.size(); ++i){
		stack.push_back(new Stack(orig.at(i)));
	}
}

Stack& StackStack::top(){
	return at(select);
}

Stack& StackStack::second(){
	return at(select+1);
}

Stack& StackStack::at(size_t x){
	return *stack[stack.size()-x-1];
}

const Stack& StackStack::top() const{
	return at(select);
}

const Stack& StackStack::second() const{
	return at(select+1);
}

const Stack& StackStack::at(size_t x) const{
	return *stack[stack.size()-x-1];
}

void StackStack::pop(){
	Stack* old = stack.back();
	stack.pop_back();
	delete old;
}

void StackStack::push(){
	stack.push_back(new Stack());
}

void StackStack::insert(size_t pos){
	auto iter = stack.begin();
	iter += stack.size()-pos-select;
	stack.insert(iter, new Stack());
}

void StackStack::remove(size_t pos){
	auto iter = stack.begin();
	iter += stack.size()-pos-select;
	stack.erase(iter);
}

size_t StackStack::size() const{
	return stack.size();
}

void StackStack::setMode(FungeMode m){
	for(auto s : stack){
		s->setMode(m);
	}
}

FungeError StackStack::increment(){
	if(select > 0){
		--select;
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError StackStack::decrement(){
	if(select < stack.size()-1){
		++select;
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

}
