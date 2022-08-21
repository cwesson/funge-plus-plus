/**
 * @file FingerprintORTH.cpp
 * Orthogonal Easement Library.
 * @author Conlan Wesson
 */

#include "FingerprintORTH.h"
#include "FungeUtilities.h"

namespace Funge {

FingerprintORTH::FingerprintORTH(FungeRunner& r) :
	Fingerprint(r, {'A', 'E', 'G', 'O', 'P', 'S', 'V', 'W', 'X', 'Y', 'Z'})
{}

FungeError FingerprintORTH::execute(inst_t cmd){
	switch(cmd){
		case 'A':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			stack.top().push(b & a);
		} break;
		case 'E':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			stack.top().push(b ^ a);
		} break;
		case 'G':{
			stack_t x = stack.top().pop();
			stack_t y = stack.top().pop();
			Vector v({x, y});
			stack.top().push(field.get(v));
		} break;
		case 'O':{
			stack_t a = stack.top().pop();
			stack_t b = stack.top().pop();
			stack.top().push(b | a);
		} break;
		case 'P':{
			stack_t x = stack.top().pop();
			stack_t y = stack.top().pop();
			stack_t i = stack.top().pop();
			Vector v({x, y});
			field.put(v, static_cast<inst_t>(i));
		} break;
		case 'S':{
			std::string str = popString(stack.top());
			std::cout << str << std::endl;
		} break;
		case 'V':{
			stack_t dx = stack.top().pop();
			Vector d(ip.getDelta());
			d.set(0, dx);
			ip.setDelta(d);
		} break;
		case 'W':{
			stack_t dy = stack.top().pop();
			Vector d(ip.getDelta());
			d.set(1, dy);
			ip.setDelta(d);
		} break;
		case 'X':{
			stack_t x = stack.top().pop();
			Vector d(ip.getPos());
			d.set(0, x);
			ip.setPos(d);
		} break;
		case 'Y':{
			stack_t y = stack.top().pop();
			Vector d(ip.getPos());
			d.set(1, y);
			ip.setPos(d);
		} break;
		case 'Z':{
			stack_t z = stack.top().pop();
			if(z == 0){
				ip.next();
			}
		} break;
		default:
			return ERROR_UNIMP;
	}
	return ERROR_NONE;
}

}
