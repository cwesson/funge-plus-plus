/**
 * @file FingerprintSUBR.cpp
 * Subroutine extension.
 * @author Conlan Wesson
 */

#include "FingerprintSUBR.h"
#include "FungeUtilities.h"

namespace Funge {

FingerprintSUBR::FingerprintSUBR(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s, {'A', 'C', 'J', 'O', 'R'}),
	offset(false)
{}

bool FingerprintSUBR::execute(inst_t cmd){
	switch(cmd){
		case 'A':{
			offset = false;
		} break;
		case 'C':{
			stack_t n = stack.top().pop();
			Vector va = popVector(stack.top());
			stack_t pops[n];
			for(stack_t i = 0; i < n; ++i){
				pops[i] = stack.top().pop();
			}
			pushVector(stack.top(), ip.getPos());
			pushVector(stack.top(), ip.getDelta());
			for(stack_t i = n; i > 0; --i){
				stack.top().push(pops[i-1]);
			}
			if(offset){
				va += ip.getPos();
			}
			ip.setPos(va-Vector{1});
			ip.setDelta(Vector{1});
		} break;
		case 'J':{
			Vector va = popVector(stack.top());
			if(offset){
				va += ip.getPos();
			}
			ip.setPos(va);
			ip.setDelta(Vector{1});
		} break;
		case 'O':{
			offset = true;
		} break;
		case 'R':{
			stack_t n = stack.top().pop();
			stack_t pops[n];
			for(stack_t i = 0; i < n; ++i){
				pops[i] = stack.top().pop();
			}
			Vector vd = popVector(stack.top());
			Vector va = popVector(stack.top());
			for(stack_t i = n; i > 0; --i){
				stack.top().push(pops[i-1]);
			}
			ip.setPos(va);
			ip.setDelta(vd);
		} break;
		default:
			return false;
	}
	return true;
}

}
