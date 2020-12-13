/**
 * @file FingerprintBITW.cpp
 * Bitwise operators.
 * @author Conlan Wesson
 */

#include "FingerprintBITW.h"

namespace Funge {

FingerprintBITW::FingerprintBITW(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s, {'A', 'L', 'N', 'O', 'R', 'X'})
{}

bool FingerprintBITW::execute(inst_t cmd){
	switch(cmd){
		case 'A':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			stack.top().push(b & a);
		} break;
		case 'L':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			stack.top().push(b << a);
		} break;
		case 'N':{
			stack_t a = stack.top().pop();
			stack.top().push(~a);
		} break;
		case 'O':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			stack.top().push(b | a);
		} break;
		case 'R':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			stack.top().push(b >> a);
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

}
