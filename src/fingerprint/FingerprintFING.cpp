/**
 * @file FingerprintFING.cpp
 * Operate on single fingerprint semantics.
 * @author Conlan Wesson
 */

#include "FingerprintFING.h"

namespace Funge {

FingerprintFING::FingerprintFING(FungeRunner& r) :
	Fingerprint(r, {'X', 'Y', 'Z'})
{}

bool FingerprintFING::execute(inst_t cmd){
	switch(cmd){
		case 'X':{
			stack_t a = stack.top().pop();
			if(a >= 0 && a <= 25){
				a += 'A';
			}
			if(a < 'A' || a > 'Z'){
				ip.reflect();
				break;
			}
			stack_t b = stack.top().pop();
			if(b >= 0 && b <= 25){
				b += 'A';
			}
			if(b >= 'A' && b <= 'Z'){
				semantic_t sema = runner.popSemantic(a);
				semantic_t semb = runner.popSemantic(b);
				if(sema == nullptr){
					sema = std::bind(&FingerprintFING::instructionReflect, this);
				}
				if(semb == nullptr){
					semb = std::bind(&FingerprintFING::instructionReflect, this);
				}
				runner.pushSemantic(a, semb);
				runner.pushSemantic(b, sema);
			}else{
				ip.reflect();
			}
		} break;
		case 'Y':{
			stack_t a = stack.top().pop();
			if(a >= 0 && a <= 25){
				a += 'A';
			}
			if(a >= 'A' && a <= 'Z'){
				runner.popSemantic(a);
			}else{
				ip.reflect();
			}
		} break;
		case 'Z':{
			stack_t dst = stack.top().pop();
			if(dst >= 0 && dst <= 25){
				dst += 'A';
			}
			if(dst < 'A' || dst > 'Z'){
				ip.reflect();
				break;
			}
			stack_t src = stack.top().pop();
			if(src >= 0 && src <= 25){
				src += 'A';
			}
			if(src >= 'A' && src <= 'Z'){
				semantic_t sem = runner.getSemantic(src);
				if(sem == nullptr){
					sem = std::bind(&FingerprintFING::instructionReflect, this);
				}
				runner.pushSemantic(dst, sem);
			}else{
				ip.reflect();
			}
		} break;
		default:
			return false;
	}
	return true;
}


bool FingerprintFING::instructionReflect(){
	ip.reflect();
	return true;
}

}
