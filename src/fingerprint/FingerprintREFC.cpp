/**
 * @file FingerprintREFC.cpp
 * Referenced Cells Extension.
 * @author Conlan Wesson
 */

#include "FingerprintREFC.h"
#include "FungeUtilities.h"

namespace Funge {

std::map<stack_t, Vector> FingerprintREFC::refc_map;

FingerprintREFC::FingerprintREFC(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s, {'R', 'D'})
{}

bool FingerprintREFC::execute(inst_t cmd){
	switch(cmd){
		case 'R':{
			Vector v = popVector(stack.top());
			stack_t r = random();
			auto find = refc_map.find(r);
			while(find != refc_map.end()){
				r = random();
				find = refc_map.find(r);
			}
			refc_map[r] = v;
			stack.top().push(r);
		} break;
		case 'D':{
			stack_t r = stack.top().pop();
			auto find = refc_map.find(r);
			if(find != refc_map.end()){
				Vector v = refc_map[r];
				pushVector(stack.top(), v);
			}
		} break;
		default:
			return false;
	}
	return true;
}

}
