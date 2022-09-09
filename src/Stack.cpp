/**
 * @file Stack.cpp
 * Wrapper around list in order to handle Befunge style stacks.
 * @author Conlan Wesson
 */

#include "Stack.h"
#include "FungeRunner.h"

namespace Funge {

Stack::Stack() :
	mode(),
	stack(),
	ops(0),
	mutex()
{
	
}

Stack::Stack(const Stack& orig) :
	mode(),
	stack(orig.stack),
	ops(0),
	mutex()
{
	
}

stack_t Stack::pop(){
	std::lock_guard<std::mutex> lock(mutex);
	stack_t ret = 0;
	if(!stack.empty()){
		if(mode & FUNGE_MODE_QUEUE){
			ret = stack.front();
			stack.pop_front();
		}else{
			ret = stack.back();
			stack.pop_back();
		}
	}
	++ops;
	return ret;
}

stack_t Stack::peek() const{
	std::lock_guard<std::mutex> lock(mutex);
	stack_t ret = 0;
	if(!stack.empty()){
		if(mode & FUNGE_MODE_QUEUE){
			ret = stack.front();
		}else{
			ret = stack.back();
		}
	}
	return ret;
}

size_t Stack::push(stack_t v){
	std::lock_guard<std::mutex> lock(mutex);
	if(mode & FUNGE_MODE_INVERT){
		stack.push_front(v);
	}else{
		stack.push_back(v);
	}
	++ops;
	return 1;
}

void Stack::clear(){
	std::lock_guard<std::mutex> lock(mutex);
	stack.clear();
	++ops;
}

size_t Stack::size() const{
	return stack.size();
}

size_t Stack::age() const{
	return ops;
}

stack_t Stack::get(size_t p) const{
	std::lock_guard<std::mutex> lock(mutex);
	if(p <= stack.size() && p > 0){
		--p;
		if(mode & FUNGE_MODE_QUEUE){
			auto it = stack.begin();
			for( ; p > 0; --p){
				++it;
			}
			return *it;
		}else{
			auto it = stack.rbegin();
			// The duplicated code is silly, but the iterators have different types
			for( ; p > 0; --p){
				++it;
			}
			return *it;
		}
	}
	return 0;
}

stack_t Stack::operator[](size_t p) const{
	return this->get(p);
}

void Stack::setMode(FungeMode m){
	mode = m;
}

}
