/**
 * @file FingerprintCPLI.cpp
 * Complex integer extension.
 * @author Conlan Wesson
 */

#include "FingerprintCPLI.h"

namespace Funge {

FingerprintCPLI::FingerprintCPLI(FungeRunner& r) :
	Fingerprint(r, {'A', 'D', 'M', 'O', 'S', 'V'})
{}

bool FingerprintCPLI::execute(inst_t cmd){
	switch(cmd){
		case 'A':{
			cpli_t b = popComplex(stack.top());
			cpli_t a = popComplex(stack.top());
			pushComplex(stack.top(), a + b);
		} break;
		case 'D':{
			cpli_t b = popComplex(stack.top());
			cpli_t a = popComplex(stack.top());
			cplf_t da = toDouble(a);
			cplf_t db = toDouble(b);
			pushComplex(stack.top(), toInt(da / db));
		} break;
		case 'M':{
			cpli_t b = popComplex(stack.top());
			cpli_t a = popComplex(stack.top());
			pushComplex(stack.top(), a * b);
		} break;
		case 'O':{
			cpli_t a = popComplex(stack.top());
			stack_t r = a.real();
			stack_t i = a.imag();
			if(i == 0){
				std::cout << r << ' ';
			}else if(r == 0){
				std::cout << i << "i ";
			}else if(i < 0){
				std::cout << r << i << "i ";
			}else{
				std::cout << r << '+' << i << "i ";
			}
		} break;
		case 'S':{
			cpli_t b = popComplex(stack.top());
			cpli_t a = popComplex(stack.top());
			pushComplex(stack.top(), a - b);
		} break;
		case 'V':{
			cpli_t a = popComplex(stack.top());
			std::complex<double> d = toDouble(a);
			stack.top().push(std::round(std::abs(d)));
		} break;
		default:
			return false;
	}
	return true;
}

FingerprintCPLI::cpli_t FingerprintCPLI::popComplex(Stack& stack){
	stack_t imag = stack.pop();
	stack_t real = stack.pop();
	std::complex<stack_t> ret(real, imag);
	return ret;
}

void FingerprintCPLI::pushComplex(Stack& stack, cpli_t comp){
	stack.push(comp.real());
	stack.push(comp.imag());
}

FingerprintCPLI::cplf_t FingerprintCPLI::toDouble(cpli_t comp){
	double r = comp.real();
	double i = comp.imag();
	cplf_t d(r, i);
	return d;
}

FingerprintCPLI::cpli_t FingerprintCPLI::toInt(cplf_t comp){
	stack_t r = std::round(comp.real());
	stack_t i = std::round(comp.imag());
	cpli_t d(r, i);
	return d;
}

}
