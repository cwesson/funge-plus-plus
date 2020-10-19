/**
 * @file FingerprintTOYS.h
 * Standard Toys.
 * @author Conlan Wesson
 */

#include "FingerprintTOYS.h"
#include "FungeConfig.h"
#include "FungeUtilities.h"
#include <cmath>

namespace Funge {

FingerprintTOYS::FingerprintTOYS(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s, {
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
			'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	}),
	rd(),
	gen(rd()),
	dis()
{}

bool FingerprintTOYS::execute(inst_t cmd){
	switch(cmd){
		case 'A':{
			stack_t n = stack.top().pop();
			stack_t a = stack.top().pop();
			for(stack_t i = 0; i < n; ++i){
				stack.top().push(a);
			}
		} break;
		case 'D':{
			stack.top().push(stack.top().pop()-1);
		} break;
		case 'E':{
			stack_t sum = 0;
			while(stack.top().size() > 0){
				sum += stack.top().pop();
			}
			stack.top().push(sum);
		} break;
		case 'H':{
			stack_t b = stack.top().pop();
			stack_t a = stack.top().pop();
			if(b > 0){
				a <<= b;
			}else{
				a >>= -b;
			}
			stack.top().push(a);
		} break;
		case 'I':{
			stack.top().push(stack.top().pop()+1);
		} break;
		case 'L':{
			Vector delta = ip.getDelta();
			delta.left();
			Vector v = ip.getPos() + delta;
			stack_t a = field.get(v);
			stack.top().push(a);
		} break;
		case 'N':{
			stack.top().push(!stack.top().pop());
		} break;
		case 'P':{
			stack_t product = 1;
			while(stack.top().size() > 0){
				product *= stack.top().pop();
			}
			stack.top().push(product);
		} break;
		case 'Q':{
			Vector delta = ip.getDelta();
			delta.reverse();
			Vector v = ip.getPos() + delta;
			stack_t a = stack.top().pop();
			field.set(v, a);
		} break;
		case 'R':{
			Vector delta = ip.getDelta();
			delta.right();
			Vector v = ip.getPos() + delta;
			stack_t a = field.get(v);
			stack.top().push(a);
		} break;
		case 'T':{
			size_t n = static_cast<size_t>(stack.top().pop());
			Vector v;
			if(stack.top().pop() == 0){
				v.set(n, 1);
			}else{
				v.set(n, -1);
			}
			ip.setDelta(v);
			if(funge_config.dimensions < n){
				funge_config.dimensions = n;
			}
		} break;
		case 'U':{
				size_t d = std::min(funge_config.dimensions, static_cast<size_t>(3))*2;
				int r = dis(gen)%d;
				Vector v;
				if(r & 1){
					v.set(r>>1, -1);
				}else{
					v.set(r>>1, 1);
				}
				inst_t inst = '?';
				switch(r){
					case 0:
						inst = '>';
						break;
					case 1:
						inst = '<';
						break;
					case 2:
						inst = 'v';
						break;
					case 3:
						inst = '^';
						break;
					case 4:
						inst = 'h';
						break;
					case 5:
						inst = 'l';
						break;
				}
				ip.set(inst);
				ip.setDelta(v);
				break;
		}
		case 'W':{
			Vector v = popVector(stack.top());
			stack_t value = stack.top().pop();
			stack_t cell = field.get(v);
			if(cell < value){
				stack.top().push(value);
				pushVector(stack.top(), v);
				ip.reverse();
				ip.next();
				ip.reverse();
			}else if(cell > value){
				ip.reverse();
			}
		} break;
		case 'X':{
			Vector inc(ip.getPos());
			inc.set(0, inc.get(0)+1);
			ip.setPos(inc);
		} break;
		case 'Y':{
			Vector inc(ip.getPos());
			inc.set(1, inc.get(1)+1);
			ip.setPos(inc);
		} break;
		case 'Z':{
			Vector inc(ip.getPos());
			inc.set(2, inc.get(2)+1);
			ip.setPos(inc);
		} break;
		default:
			return false;
	}
	return true;
}

}
