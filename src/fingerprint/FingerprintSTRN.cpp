/**
 * @file FingerprintSTRN.cpp
 * String functions.
 * @author Conlan Wesson
 */

#include "FingerprintSTRN.h"
#include "FungeUtilities.h"

namespace Funge {

FingerprintSTRN::FingerprintSTRN(FungeRunner& r) :
	Fingerprint(r, {'A', 'C', 'D', 'F', 'G', 'I', 'L', 'M', 'N', 'P', 'R', 'S', 'V'})
{}

FungeError FingerprintSTRN::execute(inst_t cmd){
	FungeError ret = ERROR_NONE;
	switch(cmd){
		case 'A':{
			std::string upper = popString(stack.top());
			std::string bottom = popString(stack.top());
			pushString(stack.top(), upper.append(bottom));
		} break;
		case 'C':{
			std::string upper = popString(stack.top());
			std::string bottom = popString(stack.top());
			stack.top().push(upper.compare(bottom));
		} break;
		case 'D':{
			std::string str = popString(stack.top());
			std::cout << str;
		} break;
		case 'F':{
			std::string upper = popString(stack.top());
			std::string bottom = popString(stack.top());
			size_t n = upper.find(bottom);
			if(n != std::string::npos){
				pushString(stack.top(), upper.substr(n));
			}else{
				stack.top().push(0);
			}
		} break;
		case 'G':{
			Vector va = popVector(runner);
			va += ip.getStorage();
			std::string str;
			for( ; field.get(va); va += Vector{1}){
				str += field.get(va);
			}
			pushString(stack.top(), str);
		} break;
		case 'I':{
			std::string str;
			std::getline(std::cin, str);
			pushString(stack.top(), str);
		} break;
		case 'L':{
			stack_t n = stack.top().pop();
			if(n < 0){
				ret = ERROR_UNSPEC;
				break;
			}
			std::string str = popString(stack.top());
			pushString(stack.top(), str.substr(0, n));
		} break;
		case 'M':{
			stack_t n = stack.top().pop();
			stack_t s = stack.top().pop();
			if(n < 0 || s < 0){
				ret = ERROR_UNSPEC;
				break;
			}
			std::string str = popString(stack.top());
			if(static_cast<size_t>(s) > str.length()){
				ret = ERROR_UNSPEC;
				break;
			}
			pushString(stack.top(), str.substr(s, n));
		} break;
		case 'N':{
			std::string str = popString(stack.top());
			pushString(stack.top(), str);
			stack.top().push(str.length());
		} break;
		case 'P':{
			Vector va = popVector(runner);
			va += ip.getStorage();
			std::string str = popString(stack.top());
			for(char c : str){
				field.set(va, c);
				va += Vector{1};
			}
			field.set(va, 0);
		} break;
		case 'R':{
			stack_t n = stack.top().pop();
			if(n < 0){
				ret = ERROR_UNSPEC;
				break;
			}
			std::string str = popString(stack.top());
			if(static_cast<size_t>(n) > str.length()){
				n = str.length();
			}
			pushString(stack.top(), str.substr(str.length()-n));
		} break;
		case 'S':{
			stack_t n = stack.top().pop();
			pushString(stack.top(), std::to_string(n));
		} break;
		case 'V':{
			std::string str = popString(stack.top());
			stack.top().push(std::stoi(str));
		} break;
		default:
			ret = ERROR_UNIMP;
	}
	return ret;
}

}
