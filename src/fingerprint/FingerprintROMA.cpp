/**
 * @file FingerprintROMA.cpp
 * Roman Numerals.
 * @author Conlan Wesson
 */

#include "FingerprintROMA.h"

namespace Funge {

const std::string FingerprintROMA::hundreds[9] = {
	"C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"
};


const std::string FingerprintROMA::tens[9] = {
	"X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"
};

const std::string FingerprintROMA::ones[9] = {
	"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"
};

FingerprintROMA::FingerprintROMA(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s, {'C', 'D', 'I', 'L', 'M', 'P', 'V', 'X'})
{}

bool FingerprintROMA::execute(inst_t cmd){
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
		case 'P':{
			stack_t n = stack.top().pop();
			print(n);
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

void FingerprintROMA::print(stack_t n){
	if(n <= 0){
		std::cout << "0 ";
		return;
	}
	for( ; n >= 1000; n -= 1000){
		std::cout << 'M';
	}
	if(n >= 100){
		stack_t h = n / 100;
		std::cout << hundreds[h-1];
		n -= h*100;
	}
	if(n >= 10){
		stack_t t = n / 10;
		std::cout << tens[t-1];
		n -= t*10;
	}
	if(n >= 1){
		std::cout << ones[n-1];
	}
	std::cout << ' ';
}

}
