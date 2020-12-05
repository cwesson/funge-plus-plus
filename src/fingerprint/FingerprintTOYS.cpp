/**
 * @file FingerprintTOYS.h
 * Standard Toys.
 * @author Conlan Wesson
 */

#include "FingerprintTOYS.h"
#include "FungeConfig.h"
#include "FungeUtilities.h"
#include "VectorRange.h"
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
		case 'B':{
			stack_t b = stack.top().pop();
			stack_t a = stack.top().pop();
			stack.top().push(a+b);
			stack.top().push(a-b);
		} break;
		case 'C':{
			Vector dest = popVector(stack.top());
			Vector size = popVector(stack.top());
			Vector src = popVector(stack.top());
			copySpace(src, size, dest, true, false);
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
		case 'F':{
			Vector dest = popVector(stack.top());
			Vector size = popVector(stack.top());
			if(sizeToRange(size)){
				VectorRange range(Vector({0}), size);
				for(range.begin(); *range != range.end(); ++range){
					field.set(dest + *range, stack.top().pop());
				}
			}
		} break;
		case 'G':{
			Vector src = popVector(stack.top());
			Vector size = popVector(stack.top());
			if(sizeToRange(size)){
				VectorRange range(size, Vector({0}));
				for(range.begin(); *range != range.end(); ++range){
					stack.top().push(field.get(src + *range));
				}
			}
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
		case 'J':{
			dim_t n = stack.top().pop();
			if(n != 0){
				dim_t ymin = field.min(1);
				dim_t ymax = field.max(1);
				dim_t x = ip.getPos().get(0);
				copySpace(Vector({x, ymin}), Vector({1, ymax-ymin}), Vector({x, ymin+n}), (n < 0), true);
			}
		} break;
		case 'K':{
			Vector dest = popVector(stack.top());
			Vector size = popVector(stack.top());
			Vector src = popVector(stack.top());
			copySpace(src, size, dest, false, false);
		} break;
		case 'L':{
			Vector delta = ip.getDelta();
			delta.left();
			Vector v = ip.getPos() + delta;
			stack_t a = field.get(v);
			stack.top().push(a);
		} break;
		case 'M':{
			Vector dest = popVector(stack.top());
			Vector size = popVector(stack.top());
			Vector src = popVector(stack.top());
			copySpace(src, size, dest, true, true);
		} break;
		case 'N':{
			stack.top().push(!stack.top().pop());
		} break;
		case 'O':{
			dim_t n = stack.top().pop();
			if(n != 0){
				dim_t xmin = field.min(0);
				dim_t xmax = field.max(0);
				dim_t y = ip.getPos().get(1);
				copySpace(Vector({xmin, y}), Vector({xmax-xmin, 1}), Vector({xmin+n, y}), (n < 0), true);
			}
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
		case 'S':{
			Vector dest = popVector(stack.top());
			Vector size = popVector(stack.top());
			inst_t i = stack.top().pop();
			if(sizeToRange(size)){
				VectorRange range(Vector({0}), size);
				for(range.begin(); *range != range.end(); ++range){
					field.set(dest + *range, i);
				}
			}
		} break;
		case 'T':{
			size_t n = static_cast<size_t>(stack.top().pop());
			Vector v;
			if(stack.top().pop() == 0){
				v.set(n, 1);
			}else{
				v.set(n, -1);
			}
			if(funge_config.dimensions > n){
				ip.setDelta(v);
			}else{
				ip.reverse();
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
		} break;
		case 'V':{
			Vector dest = popVector(stack.top());
			Vector size = popVector(stack.top());
			Vector src = popVector(stack.top());
			copySpace(src, size, dest, false, true);
		} break;
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
			if(funge_config.dimensions > 1){
				Vector inc(ip.getPos());
				inc.set(1, inc.get(1)+1);
				ip.setPos(inc);
			}else{
				ip.reverse();
			}
		} break;
		case 'Z':{
			if(funge_config.dimensions > 2){
				Vector inc(ip.getPos());
				inc.set(2, inc.get(2)+1);
				ip.setPos(inc);
			}else{
				ip.reverse();
			}
		} break;
		default:
			return false;
	}
	return true;
}

void FingerprintTOYS::copySpace(const Vector& src, const Vector& sz, const Vector& dest, bool low, bool move){
	Vector bound(sz);
	if(sizeToRange(bound)){
		Vector start, end;
		//std::cout << "Copy from " << src << bound << " to " << dest << std::endl;
		if(low){
			start = Vector({0});
			end = bound;
		}else{
			start = bound;
			end = Vector({0});
		}
		VectorRange range(start, end);
		for(range.begin(); *range != range.end(); ++range){
			inst_t i = field.get(src + *range);
			field.set(dest + *range, i);
			if(move){
				field.set(src + *range, ' ');
			}
		}
	}
}

bool FingerprintTOYS::sizeToRange(Vector& size){
	for(size_t d = 0; d < size.size(); ++d){
		dim_t s = size.get(d);
		if(s > 0){
			size.set(d, s-1);
		}else if(s < 0){
			size.set(d, s+1);
		}else{
			return false;
		}
	}
	return true;
}

}
