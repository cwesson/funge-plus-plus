/**
 * @file FingerprintREFC.cpp
 * Referenced Cells Extension.
 * @author Conlan Wesson
 */

#include "FingerprintREFC.h"
#include "FungeUtilities.h"

namespace Funge {

std::map<stack_t, Vector> FingerprintREFC::refc_map;

FingerprintREFC::FingerprintREFC(FungeRunner& r) :
	Fingerprint(r, {'R', 'D'})
{}

FungeError FingerprintREFC::execute(inst_t cmd){
	switch(cmd){
		case 'R':{
			Vector v = popVector(runner);
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
				pushVector(runner, v);
			}
		} break;
		default:
			return ERROR_UNIMP;
	}
	return ERROR_NONE;
}

}
