/**
 * @file FingerprintNFUN.cpp
 * N-Dimensional Funge.
 * @author Conlan Wesson
 */

#include "FingerprintNFUN.h"
#include "FungeConfig.h"

namespace Funge {

FingerprintNFUN::FingerprintNFUN(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s,
			{'A', 'B', 'H', 'I', 'L', 'M', 'Q', 'T', 'U', 'V', 'X', 'Y', 'Z'})
{}

bool FingerprintNFUN::execute(inst_t cmd){
	size_t dim = 0;
	switch(cmd){
		case 'A':{
			ip.setDelta(Vector{0, 0, 0, -1});
			dim = 4;
		} break;
		case 'C':{
			ip.setDelta(Vector{0, 0, 0, 0, 0, -1});
			dim = 6;
		} break;
		case 'D':{
			ip.setDelta(Vector{0, 0, 0, 0, 0, 1});
			dim = 6;
		} break;
		case 'H':{
			ip.setDelta(Vector{0, 0, 0, 0, -1});
			dim = 5;
		} break;
		case 'I':{
			if(stack.top().pop() == 0){
				ip.setDelta(Vector{0, 0, 0, 1});
			}else{
				ip.setDelta(Vector{0, 0, 0, -1});
			}
			dim = 4;
		} break;
		case 'L':{
			ip.setDelta(Vector{0, 0, 0, 0, 1});
			dim = 5;
		} break;
		case 'M':{
			if(stack.top().pop() == 0){
				ip.setDelta(Vector{0, 0, 0, 0, 1});
			}else{
				ip.setDelta(Vector{0, 0, 0, 0, -1});
			}
			dim = 5;
		} break;
		case 'R':{
			if(stack.top().pop() == 0){
				ip.setDelta(Vector{0, 0, 0, 0, 0, 1});
			}else{
				ip.setDelta(Vector{0, 0, 0, 0, 0, -1});
			}
			dim = 6;
		} break;
		case 'V':{
			ip.setDelta(Vector{0, 0, 0, 1});
			dim = 4;
		} break;
		case 'X':{
			stack_t n = stack.top().pop();
			Vector v;
			if(stack.top().pop() == 0){
				v.set(n, 1);
			}else{
				v.set(n, -1);
			}
			ip.setDelta(v);
			dim = n;
		} break;
		case 'Y':{
			stack_t n = stack.top().pop();
			Vector v;
			v.set(n, -1);
			ip.setDelta(v);
			dim = n;
		} break;
		case 'Z':{
			stack_t n = stack.top().pop();
			Vector v;
			v.set(n, 1);
			ip.setDelta(v);
			dim = n;
		} break;
		default:
			return false;
	}
	if(funge_config.dimensions < dim){
		funge_config.dimensions = dim;
	}
	return true;
}

}
