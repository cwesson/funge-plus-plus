/**
 * @file FingerprintFPRT.h
 * Formatted print.
 * @author Conlan Wesson
 */

#include "FingerprintFPRT.h"
#include "FungeUtilities.h"

namespace Funge {

FingerprintFPRT::FingerprintFPRT(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s, {'D', 'F', 'I', 'L', 'S'})
{}

bool FingerprintFPRT::execute(inst_t cmd){
	switch(cmd){
		case 'D':{
			stack_t n = stack.top().pop();
			std::string fmt = popString(stack.top());
			double f = *reinterpret_cast<double*>(&n);
			char str[1024];
			int ret = snprintf(str, sizeof(str), fmt.c_str(), f);
			if(ret < 0){
				ip.reflect();
				break;
			}
			pushString(stack.top(), std::string(str));
		} break;
		case 'F':{
			stack_t n = stack.top().pop();
			std::string fmt = popString(stack.top());
			double f = *reinterpret_cast<float*>(&n);
			char str[1024];
			int ret = snprintf(str, sizeof(str), fmt.c_str(), f);
			if(ret < 0){
				ip.reflect();
				break;
			}
			pushString(stack.top(), std::string(str));
		} break;
		case 'I':{
			stack_t i = stack.top().pop();
			std::string fmt = popString(stack.top());
			char str[1024];
			int ret = snprintf(str, sizeof(str), fmt.c_str(), i);
			if(ret < 0){
				ip.reflect();
				break;
			}
			pushString(stack.top(), std::string(str));
		} break;
		case 'L':{
			stack_t l = stack.top().pop();
			stack_t h = stack.top().pop();
			std::string fmt = popString(stack.top());
			stack_t n = (h << 32) | (l & 0xFFFFFFFF);
			char str[1024];
			int ret = snprintf(str, sizeof(str), fmt.c_str(), n);
			if(ret < 0){
				ip.reflect();
				break;
			}
			pushString(stack.top(), std::string(str));
		} break;
		case 'S':{
			std::string s = popString(stack.top());
			std::string fmt = popString(stack.top());
			char str[1024];
			int ret = snprintf(str, sizeof(str), fmt.c_str(), s.c_str());
			if(ret < 0){
				ip.reflect();
				break;
			}
			pushString(stack.top(), std::string(str));
		} break;
		default:
			return false;
	}
	return true;
}

}
