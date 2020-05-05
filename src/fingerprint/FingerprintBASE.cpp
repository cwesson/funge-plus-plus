/**
 * @file FingerprintBASE.cpp
 * I/O for numbers in other bases.
 * @author Conlan Wesson
 */

#include "FingerprintBASE.h"
#include <iostream>

namespace Funge {

char FingerprintBASE::digit_map[32] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K',
	'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X',
	'Y', 'Z'
};

FingerprintBASE::FingerprintBASE(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s,
			{'B', 'H', 'I', 'N', 'O'})
{}

bool FingerprintBASE::execute(inst_t cmd){
	switch ((cmd))
	{
		case 'B':{
			stack_t a = stack.top().pop();
			printNum(a, 2);
		} break;
		case 'H':{
			stack_t a = stack.top().pop();
			printNum(a, 16);
		} break;
		case 'I':{
			stack_t b = stack.top().pop();
			stack_t i = readNum(b);
			stack.top().push(i);
		} break;
		case 'N':{
			stack_t b = stack.top().pop();
			stack_t a = stack.top().pop();
			printNum(a, b);
		} break;
		case 'O':{
			stack_t a = stack.top().pop();
			printNum(a, 8);
		} break;
		
		default:
			return false;
	}
	return true;
}

void FingerprintBASE::printNum(stack_t num, unsigned int base){
	if(base > 1){
		printBase(num, base, true);
	}else{
		for(stack_t i = 0; i < num; ++i){
			std::cout << "0";
		}
	}
	std::cout << " " << std::flush;
}

void FingerprintBASE::printBase(stack_t num, unsigned int base, bool low){
	stack_t digit = num % base;
	stack_t next = num / base;
	if(next > 0){
		printBase(next, base, false);
	}
	if(base <= sizeof(digit_map)){
		std::cout << digit_map[digit];
	}else{
		std::cout << digit;
		if(!low){
			std::cout << ",";
		}
	}
}

stack_t FingerprintBASE::readNum(unsigned int base){
	std::string str;
	std::cin >> str;
	stack_t num = 0;
	if(base <= 1){
		num = str.size();
	}else if(base <= sizeof(digit_map)){
		readBase(str, &num, base);
	}
	return num;
}

bool FingerprintBASE::readBase(std::string str, stack_t* num, unsigned int base){
	char digit = str[0];
	bool found = false;
	for(size_t i = 0; i <= base; ++i){
		if(digit_map[i] == digit){
			*num = (*num*base) + i;
			found = true;
			break;
		}
	}
	if(found && str.size() > 1){
		str.erase(0, 1);
		readBase(str, num, base);
	}
	return true;
}

}
