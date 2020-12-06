/**
 * @file FingerprintROMA.cpp
 * Roman Numerals.
 * @author Conlan Wesson
 */

#include "FingerprintROMA.h"

namespace Funge {

FingerprintROMA::FingerprintROMA(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s, {'C', 'D', 'I', 'L', 'M', 'V', 'X'})
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

}
