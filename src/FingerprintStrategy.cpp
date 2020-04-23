/**
 * @file FingerprintStrategy.cpp
 * Strategy for fingerprint commands.
 * @author Conlan Wesson
 */

#include "FingerprintStrategy.h"
#include "FungeUtilities.h"

namespace Funge {

FingerprintStrategy::FingerprintStrategy(Field& f, InstructionPointer& i, StackStack& s) :
	FungeStrategy(f, i, s),
	available(),
	loaded()
{
	available[0x4e554c4c] = std::bind(&FingerprintStrategy::execute_null, this, std::placeholders::_1);
	available[0x4f525448] = std::bind(&FingerprintStrategy::execute_orth, this, std::placeholders::_1);
	available[0x52454643] = std::bind(&FingerprintStrategy::execute_refc, this, std::placeholders::_1);
	available[0x524f4d41] = std::bind(&FingerprintStrategy::execute_roma, this, std::placeholders::_1);
}

bool FingerprintStrategy::execute(inst_t cmd){
	bool done = false;
	for(auto f = loaded.crbegin(); f != loaded.crend() && !done; ++f){
		auto found = available.find(*f);
		if(found != available.cend()){
			done = found->second(cmd);
		}
	}
	return done;
}

bool FingerprintStrategy::load(uint64_t fingerprint){
	if(available.find(fingerprint) != available.cend()){
		loaded.push_back(fingerprint);
		return true;
	}
	return false;
}

bool FingerprintStrategy::unload(uint64_t fingerprint){
	for(auto f = loaded.cbegin(); f != loaded.cend(); ++f){
		if(*f == fingerprint){
			loaded.erase(f);
			return true;
		}
	}
	return false;
}

bool FingerprintStrategy::execute_null(inst_t cmd){
	if(cmd >= 'A' && cmd <= 'Z'){
		ip.reverse();
		return true;
	}
	return false;
}

bool FingerprintStrategy::execute_orth(inst_t cmd){
	switch(cmd){
		case 'A':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			stack.top().push(b & a);
		} break;
		case 'O':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			stack.top().push(b | a);
		} break;
		case 'E':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			stack.top().push(b ^ a);
		} break;
		case 'S':{
			std::string str = popString(stack.top());
			std::cout << str << std::endl;
		} break;
		case 'V':{
			stack_t dx = stack.top().pop();
			Vector d(ip.getDelta());
			d.set(0, dx);
			ip.setDelta(d);
		} break;
		case 'W':{
			stack_t dy = stack.top().pop();
			Vector d(ip.getDelta());
			d.set(1, dy);
			ip.setDelta(d);
		} break;
		case 'Z':{
			stack_t z = stack.top().pop();
			if(z == 0){
				ip.next();
			}
		} break;
		default:
			return false;
	}
	return true;
}

bool FingerprintStrategy::execute_refc(inst_t cmd){
	switch(cmd){
		case 'C':{
			Vector *v = new Vector();
			popVector(stack.top(), *v);
			stack.top().push(reinterpret_cast<stack_t>(v));
		} break;
		case 'D':{
			Vector *v = reinterpret_cast<Vector*>(stack.top().pop());
			pushVector(stack.top(), *v);
			delete v;
		} break;
		default:
			return false;
	}
	return true;
}

bool FingerprintStrategy::execute_roma(inst_t cmd){
	switch(cmd){
		case 'C':{
			stack.top().push(100);
		} break;
		case 'D':{
			stack.top().push(500);
		} break;
		case 'I':{
			stack.top().push(1);
		} break;
		case 'L':{
			stack.top().push(50);
		} break;
		case 'M':{
			stack.top().push(1000);
		} break;
		case 'V':{
			stack.top().push(5);
		} break;
		case 'X':{
			stack.top().push(10);
		} break;
		default:
			return false;
	}
	return true;
}

}
