/**
 * @file FingerprintFISH.cpp
 * Some common ><> and *><> commands.
 * @author Conlan Wesson
 */

#include "FingerprintFISH.h"
#include "FungeUniverse.h"

namespace Funge {

FingerprintFISH::FingerprintFISH(FungeRunner& r) :
	Fingerprint(r, {'C', 'D', 'F', 'H', 'I', 'L', 'M', 'N', 'O', 'R', 'S', 'T', 'U', 'V'}),
	fisherstate(FISHER_UP),
	fishercache({1, 0})
{
	ip.addObserver(std::bind(&FingerprintFISH::fishermanChange, this, std::placeholders::_1));
}

void FingerprintFISH::activate(){
	for(auto i : inst){
		if(i == 'U' || i == 'O' || i == 'M' || i == 'N' || i == 'H' || i == 'V'){
			runner.pushSemantic(i, std::bind(&Fingerprint::execute, this, i), FungeSemantic::MOVEMENT);
		}else{
			runner.pushSemantic(i, std::bind(&Fingerprint::execute, this, i));
		}
	}
}

FungeError FingerprintFISH::execute(inst_t cmd){
	FungeError ret = ERROR_NONE;
	switch(cmd){
		// Conditional trampoline
		case 'C':{
			if(!stack.top().pop()){
				ip.next();
			}
		} break;
		// Decrement Stack
		case 'D':{
			ret = stack.decrement();
		} break;
		// Fisherman
		case 'F':{
			if(ip.getDelta().get(1) == 0){
				if(fisherstate == FISHER_UP){
					ip.setDelta(Vector{0, 1});
					fisherstate = FISHER_DOWN;
				}else{
					ip.setDelta(Vector{0, -1});
					fisherstate = FISHER_UP;
				}
			}else{
				ip.setDelta(fishercache);
			}
		} break;
		// Horizontal Mirror
		case 'H':{
			Vector v = ip.getDelta();
			v.set(1, -v.get(1));
			ip.setDelta(v);
		} break;
		// Increment Stack
		case 'I':{
			ret = stack.increment();
		} break;
		// Shift Stack Left
		case 'L':{
			stack_t len = stack.top().size();
			stack_t temp[len];
			for(stack_t i = 0; i < len; ++i){
				temp[i] = stack.top().pop();
			}
			for(stack_t i = len-1; i > 0; --i){
				stack.top().push(temp[i-1]);
			}
			stack.top().push(temp[len-1]);
		} break;
		// Mirror
		case 'M':{
			Vector v = ip.getDelta();
			dim_t y = v.get(1);
			v.set(1, -v.get(0));
			v.set(0, -y);
			ip.setDelta(v);
		} break;
		case 'N':{
			Vector v = ip.getDelta();
			dim_t y = v.get(1);
			v.set(1, v.get(0));
			v.set(0, y);
			ip.setDelta(v);
		} break;
		// Rise
		case 'O':{
			runner.getUniverse().clearMode(FUNGE_MODE_DIVE);
		} break;
		// Shift Stack Left
		case 'R':{
			stack_t len = stack.top().size();
			stack_t temp[len];
			for(stack_t i = 0; i < len; ++i){
				temp[i] = stack.top().pop();
			}
			stack.top().push(temp[0]);
			for(stack_t i = len-1; i > 0; --i){
				stack.top().push(temp[i]);
			}
		} break;
		// Reverse Stack
		case 'S':{
			stack_t len = stack.top().size();
			stack_t temp[len];
			for(stack_t i = 0; i < len; ++i){
				temp[i] = stack.top().pop();
			}
			for(stack_t i = 0; i < len; ++i){
				stack.top().push(temp[i]);
			}
		} break;
		// Swap Three
		case 'T':{
			stack_t x = stack.top().pop();
			stack_t y = stack.top().pop();
			stack_t z = stack.top().pop();
			stack.top().push(x);
			stack.top().push(z);
			stack.top().push(y);
		} break;
		// Dive
		case 'U':{
			runner.getUniverse().setMode(FUNGE_MODE_DIVE);
		} break;
		// Vertical Mirror
		case 'V':{
			Vector v = ip.getDelta();
			v.set(0, -v.get(0));
			ip.setDelta(v);
		} break;
		default:
			ret = ERROR_UNIMP;
	}
	return ret;
}

void FingerprintFISH::fishermanChange(const Vector& delta){
	if(delta.get(0) != 0 && delta.get(1) == 0){
		fishercache = delta;
	}
}

}
