/**
 * @file FingerprintFIXP.cpp
 * Fixed point math functions.
 * @author Conlan Wesson
 */

#include "FingerprintFIXP.h"
#include <cmath>

namespace Funge {

FingerprintFIXP::FingerprintFIXP(FungeRunner& r) :
	Fingerprint(r, {'A', 'B', 'C', 'D', 'I', 'J', 'N', 'O', 'P', 'Q',
			'R', 'S', 'T', 'U', 'V', 'X'}),
	rd(),
	gen(rd())
{}

bool FingerprintFIXP::execute(inst_t cmd){
	switch(cmd){
		case 'A':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			stack.top().push(b & a);
		} break;
		case 'B':{
			double n = stackToFloat(stack.top().pop());
			n = radToDeg(std::acos(n));
			stack.top().push(floatToStack(n));
		} break;
		case 'C':{
			double n = stackToFloat(stack.top().pop());
			n = std::cos(degToRad(n));
			stack.top().push(floatToStack(n));
		} break;
		case 'D':{
			stack_t n = stack.top().pop();
			stack.top().push(random(n));
		} break;
		case 'I':{
			double n = stackToFloat(stack.top().pop());
			n = std::sin(degToRad(n));
			stack.top().push(floatToStack(n));
		} break;
		case 'J':{
			double n = stackToFloat(stack.top().pop());
			n = radToDeg(std::asin(n));
			stack.top().push(floatToStack(n));
		} break;
		case 'N':{
			stack_t n = stack.top().pop();
			stack.top().push(-n);
		} break;
		case 'O':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			stack.top().push(b | a);
		} break;
		case 'P':{
			double n = stack.top().pop();
			n *= M_PI;
			stack.top().push(n);
		} break;
		case 'Q':{
			stack_t n = stack.top().pop();
			n = std::sqrt(n);
			stack.top().push(n);
		} break;
		case 'R':{
			stack_t b = stack.top().pop();
			stack_t a = stack.top().pop();
			stack_t n = std::pow(a, b);
			stack.top().push(n);
		} break;
		case 'S':{
			stack_t n = stack.top().pop();
			if(n > 0){
				stack.top().push(1);
			}else if (n < 0){
				stack.top().push(-1);
			}else{
				stack.top().push(0);
			}
		} break;
		case 'T':{
			double n = stackToFloat(stack.top().pop());
			n = std::tan(degToRad(n));
			stack.top().push(floatToStack(n));
		} break;
		case 'U':{
			double n = stackToFloat(stack.top().pop());
			n = radToDeg(std::atan(n));
			stack.top().push(floatToStack(n));
		} break;
		case 'V':{
			stack_t n = stack.top().pop();
			n = std::abs(n);
			stack.top().push(n);
		} break;
		case 'X':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			stack.top().push(b ^ a);
		} break;
		default:
			return false;
	}
	return true;
}

double FingerprintFIXP::stackToFloat(stack_t n){
	return static_cast<double>(n) / 10000.0;
}

stack_t FingerprintFIXP::floatToStack(double n)
{
	return static_cast<stack_t>(std::round(n * 10000.0));
}

double FingerprintFIXP::degToRad(double deg){
	return (deg * M_PI) / 180.0;
}

double FingerprintFIXP::radToDeg(double deg){
	return (deg * 180.0) / M_PI;
}

stack_t FingerprintFIXP::random(stack_t max){
	std::uniform_int_distribution<> dis(0, max);
	return dis(gen);
}

}
