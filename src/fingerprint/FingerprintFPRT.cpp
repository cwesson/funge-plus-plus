/**
 * @file FingerprintFPRT.h
 * Formatted print.
 * @author Conlan Wesson
 */

#include "FingerprintFPRT.h"
#include "FungeUtilities.h"

namespace Funge {

FingerprintFPRT::FingerprintFPRT(FungeRunner& r) :
	Fingerprint(r, {'D', 'F', 'I', 'L', 'S'})
{}

FungeError FingerprintFPRT::execute(inst_t cmd){
	FungeError ret = ERROR_NONE;
	switch(cmd){
		case 'D':{
			stack_t n = stack.top().pop();
			std::string fmt = popString(stack.top());
			double f = *reinterpret_cast<double*>(&n);
			char str[1024];
			int ret = snprintf(str, sizeof(str), fmt.c_str(), f);
			if(ret < 0){
				ret = ERROR_UNSPEC;
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
				ret = ERROR_UNSPEC;
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
				ret = ERROR_UNSPEC;
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
				ret = ERROR_UNSPEC;
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
				ret = ERROR_UNSPEC;
				break;
			}
			pushString(stack.top(), std::string(str));
		} break;
		default:
			ret = ERROR_UNIMP;
	}
	return ret;
}

}
