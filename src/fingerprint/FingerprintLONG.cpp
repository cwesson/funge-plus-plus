/**
 * @file FingerprintLONG.cpp
 * Long Integers.
 * @author Conlan Wesson
 */

#include "FingerprintLONG.h"
#include "FungeUtilities.h"

namespace Funge {

FingerprintLONG::FingerprintLONG(FungeRunner& r) :
	Fingerprint(r, {'A', 'B', 'D', 'E', 'L', 'M', 'N', 'O', 'P', 'R', 'S', 'Z'})
{}

FungeError FingerprintLONG::execute(inst_t cmd){
	switch(cmd){
		case 'A':{
			fungelong_t b = popLong();
			fungelong_t a = popLong();
			fungelong_t r = a + b;
			pushLong(r);
		} break;
		case 'B':{
			fungelong_t a = popLong();
			if(a < 0){
				a = -a;
			}
			pushLong(a);
		} break;
		case 'D':{
			fungelong_t b = popLong();
			fungelong_t a = popLong();
			if(b != 0){
				fungelong_t r = a / b;
				pushLong(r);
			}else{
				pushLong(0);
			}
		} break;
		case 'E':{
			stack_t n = stack.top().pop();
			stack_t hi = 0;
			if(n < 0){
				hi = -1;
			}
			fungelong_t r(hi, n);
			pushLong(r);
		} break;
		case 'L':{
			stack_t n = stack.top().pop();
			fungelong_t a = popLong();
			fungelong_t r = a << n;
			pushLong(r);
		} break;
		case 'M':{
			fungelong_t b = popLong();
			fungelong_t a = popLong();
			fungelong_t r = a * b;
			pushLong(r);
		} break;
		case 'N':{
			fungelong_t a = popLong();
			pushLong(-a);
		} break;
		case 'O':{
			fungelong_t b = popLong();
			fungelong_t a = popLong();
			if(b != 0){
				fungelong_t r = a % b;
				pushLong(r);
			}else{
				pushLong(0);
			}
		} break;
		case 'P':{
			fungelong_t a = popLong();
			std::cout << a << ' ';
		} break;
		case 'R':{
			stack_t n = stack.top().pop();
			fungelong_t a = popLong();
			fungelong_t r = a >> n;
			pushLong(r);
		} break;
		case 'S':{
			fungelong_t b = popLong();
			fungelong_t a = popLong();
			fungelong_t r = a + b;
			pushLong(r);
		} break;
		case 'Z':{
			std::string str = popString(stack.top());
			fungelong_t l = 0;
			for(auto a : str){
				l *= 10;
				l += (a - '0');
			}
			pushLong(l);
		} break;
		default:
			return ERROR_UNIMP;
	}
	return ERROR_NONE;
}

FingerprintLONG::fungelong_t FingerprintLONG::popLong(){
	stack_t l = stack.top().pop();
	stack_t h = stack.top().pop();
	fungelong_t n(h, l);
	return n;
}
void FingerprintLONG::pushLong(fungelong_t n){
	stack.top().push(n.high());
	stack.top().push(n.low());
}

}
