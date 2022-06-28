/**
 * @file FingerprintIIPC.h
 * Inter-IP Communication.
 * @author Conlan Wesson
 */

#include "FingerprintIIPC.h"
#include "FungeUniverse.h"

namespace Funge {

FingerprintIIPC::FingerprintIIPC(FungeRunner& r) :
	Fingerprint(r, {'A', 'D', 'G', 'I', 'L', 'P'}),
	sage(0),
	dormant(false)
{}

FungeError FingerprintIIPC::execute(inst_t cmd){
	FungeError ret = ERROR_NONE;
	switch(cmd){
		case 'A':
			stack.top().push(runner.getParent()->getID());
			break;
		case 'D':{
			size_t age = stack.top().age();
			if(dormant){
				if(age != sage){
					dormant = false;
				}else{
					ret = ERROR_BLOCK;
				}
			}else{
				sage = age;
				dormant = true;
				ret = ERROR_BLOCK;
			}
		} break;
		case 'G':{
			size_t id = stack.top().pop();
			FungeRunner* other = runner.getUniverse().getRunner(id);
			if(other == nullptr){
				ret = ERROR_UNSPEC;
			}else{
				stack.top().push(other->getStack().top().pop());
			}
		} break;
		case 'I':
			stack.top().push(runner.getID());
			break;
		case 'L':{
			size_t id = stack.top().pop();
			FungeRunner* other = runner.getUniverse().getRunner(id);
			if(other == nullptr){
				ret = ERROR_UNSPEC;
			}else{
				stack.top().push(other->getStack().top().peek());
			}
		} break;
		case 'P':{
			size_t id = stack.top().pop();
			stack_t val = stack.top().pop();
			FungeRunner* other = runner.getUniverse().getRunner(id);
			if(other == nullptr){
				ret = ERROR_UNSPEC;
			}else{
				other->getStack().top().push(val);
			}
		} break;
		default:
			ret = ERROR_UNIMP;
	}
	return ret;
}

}
