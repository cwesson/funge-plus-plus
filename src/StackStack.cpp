/**
 * @file StackStack.cpp
 * Stack of Stacks
 * @author Conlan Wesson
 */

#include "StackStack.h"

namespace Funge {

StackStack::StackStack() :
	stack()
{
	stack.push_back(new Stack());
}

StackStack::StackStack(const StackStack& orig) :
	stack()
{
	for(size_t i = 0; i < orig.size(); ++i){
		stack.push_back(new Stack(orig.at(i)));
	}
}

Stack& StackStack::top(){
	return *stack.back();
}

Stack& StackStack::second(){
	return *stack[stack.size()-2];
}

Stack& StackStack::at(size_t x){
	return *stack[stack.size()-x-1];
}

const Stack& StackStack::top() const{
	return *stack.back();
}

const Stack& StackStack::second() const{
	return *stack[stack.size()-2];
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
	iter += stack.size()-pos;
	stack.insert(iter, new Stack());
}

void StackStack::remove(size_t pos){
	auto iter = stack.begin();
	iter += stack.size()-pos;
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

}
