/**
 * @file FingerprintTERM.cpp
 * Terminal extension.
 * @author Conlan Wesson
 */

#include "FingerprintTERM.h"

namespace Funge {

FingerprintTERM::FingerprintTERM(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s, {'C', 'D', 'G', 'H', 'L', 'S', 'U'})
{}

bool FingerprintTERM::execute(inst_t cmd){
	switch(cmd){
		case 'C':{
			std::cout << "\e[2J" << std::endl;
		} break;
		case 'D':{
			stack_t n = stack.top().pop();
			if(n >= 0){
				std::cout << "\e[" << n << "B" << std::endl;
			}else{
				std::cout << "\e[" << -n << "A" << std::endl;
			}
		} break;
		case 'G':{
			stack_t y = stack.top().pop();
			stack_t x = stack.top().pop();
			std::cout << "\e[" << x << ';' << y << 'H' << std::endl;
		} break;
		case 'H':{
			std::cout << "\e[0;0H" << std::endl;
		} break;
		case 'L':{
			std::cout << "\e[0K" << std::endl;
		} break;
		case 'S':{
			std::cout << "\e[0J" << std::endl;
		} break;
		case 'U':{
			stack_t n = stack.top().pop();
			if(n >= 0){
				std::cout << "\e[" << n << "A" << std::endl;
			}else{
				std::cout << "\e[" << -n << "B" << std::endl;
			}
		} break;
		default:
			return false;
	}
	return true;
}

}
