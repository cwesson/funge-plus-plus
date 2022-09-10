/**
 * @file FingerprintNFUN.cpp
 * N-Dimensional Funge.
 * @author Conlan Wesson
 */

#include "FingerprintNFUN.h"
#include "FungeUniverse.h"

namespace Funge {

FingerprintNFUN::FingerprintNFUN(FungeRunner& r) :
	Fingerprint(r,
			{'A', 'B', 'C', 'D', 'H', 'I', 'L', 'M', 'R', 'V', 'X', 'Y', 'Z'})
{}

void FingerprintNFUN::activate(){
	for(auto i : inst){
		if(i == 'I' || i == 'M' || i == 'R' || i == 'X' || i == 'Y' || i == 'Z'){
			runner.pushSemantic(i, std::bind(&Fingerprint::execute, this, i));
		}else{
			runner.pushSemantic(i, std::bind(&Fingerprint::execute, this, i), FungeSemantic::MOVEMENT);
		}
	}
}

FungeError FingerprintNFUN::execute(inst_t cmd){
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
			if(!runner.getUniverse().invertHL()){
				ip.setDelta(Vector{0, 0, 0, 0, 1});
			}else{
				ip.setDelta(Vector{0, 0, 0, 0, -1});
			}
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
			if(!runner.getUniverse().invertHL()){
				ip.setDelta(Vector{0, 0, 0, 0, -1});
			}else{
				ip.setDelta(Vector{0, 0, 0, 0, 1});
			}
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
			return ERROR_UNIMP;
	}
	if(runner.getUniverse().dimensions() < dim){
		runner.getUniverse().dimensions(dim);
	}
	return ERROR_NONE;
}

}
