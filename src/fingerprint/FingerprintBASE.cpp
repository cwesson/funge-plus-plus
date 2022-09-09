/**
 * @file FingerprintBASE.cpp
 * I/O for numbers in other bases.
 * @author Conlan Wesson
 */

#include "FingerprintBASE.h"
#include <algorithm>
#include <iostream>

namespace Funge {

const char FingerprintBASE::digit_map[32] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K',
	'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X',
	'Y', 'Z'
};

const char FingerprintBASE::base36[36] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X', 'Y', 'Z'
};

// Bitcoin base58
const char FingerprintBASE::base58[58] = {
	'1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K',
	'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'm', 'n', 'o', 'p', 'q',
	'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

const char FingerprintBASE::base64[64] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
	'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '+', '/'
};

// RFC 1924 base85
const char FingerprintBASE::base85[85] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'!', '#', '$', '%', '&', '(', ')', '*', '+', '-', ';', '<',
	'=', '>', '?', '@', '^', '_', '`', '{', '|', '{', '~'
};

FingerprintBASE::FingerprintBASE(FungeRunner& r) :
	Fingerprint(r, {'B', 'H', 'I', 'N', 'O'}),
	base_map()
{
	base_map[36] = &base36[0];
	base_map[58] = &base58[0];
	base_map[64] = &base64[0];
	base_map[85] = &base85[0];
}

FungeError FingerprintBASE::execute(inst_t cmd){
	switch(cmd)
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
			return ERROR_UNIMP;
	}
	return ERROR_NONE;
}

void FingerprintBASE::printNum(stack_t num, unsigned int base) const{
	if(base > 1){
		printBase(num, base, true);
	}else{
		for(stack_t i = 0; i < num; ++i){
			std::cout << "0";
		}
	}
	std::cout << " " << std::flush;
}

void FingerprintBASE::printBase(stack_t num, unsigned int base, bool low) const{
	stack_t digit = num % base;
	stack_t next = num / base;
	if(next > 0){
		printBase(next, base, false);
	}
	if(base <= sizeof(digit_map)){
		std::cout << digit_map[digit];
	}else{
		auto found = base_map.find(base);
		if(found != base_map.end()){
			std::cout << found->second[digit];
		}else{
			std::cout << digit;
			if(!low){
				std::cout << ",";
			}
		}
	}
}

stack_t FingerprintBASE::readNum(unsigned int base) const{
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

bool FingerprintBASE::readBase(std::string str, stack_t* num, unsigned int base) const{
	char digit = str[0];
	bool found = false;
	if(base <= 36){
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	}
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
