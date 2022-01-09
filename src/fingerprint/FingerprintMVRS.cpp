/**
 * @file FingerprintMVRS.cpp
 * Multiverse extension.
 * @author Conlan Wesson
 */

#include "FingerprintMVRS.h"
#include "FungeMultiverse.h"
#include "FungeUtilities.h"
#include "VectorRange.h"

namespace Funge {

FingerprintMVRS::FingerprintMVRS(FungeRunner& r) :
	Fingerprint(r, {'B', 'C', 'F', 'G', 'J', 'N', 'P'})
{}

bool FingerprintMVRS::execute(inst_t cmd){
	FungeMultiverse& multi = FungeMultiverse::getInstance();
	const FungeUniverse& universe = runner.getUniverse();
	switch(cmd){
		case 'B':{
			stack_t dim = stack.top().pop();
			stack_t lng = stack.top().pop();
			stack_t flgs = stack.top().pop();
			std::string name = popString(stack.top());
			if(dim == 0){
				dim = runner.getUniverse().dimensions();
			}
			if(flgs == 0){
				flgs = runner.getMode();
			}else if((flgs & 0x1FF) != 0){
				ip.reflect();
				return true;
			}
			switch(lng){
				case 0:
					lng = runner.getUniverse().standard();
					break;
				case 1:
					lng = 93;
					break;
				case 2:
					lng = 98;
					break;
				default:
					ip.reflect();
					return true;
			}
			FungeConfig config;
			config.name = name;
			config.dimensions = dim;
			config.standard = lng;
			config.mode = flgs;
			multi.create(&config);
		} break;
		case 'C':{
			stack.top().push(multi.size());
		} break;
		case 'F':{
			Vector size = popVector(runner);
			Vector src = popVector(runner, 3);
			Vector dest = popVector(runner);
			std::string name = popString(stack.top());
			FungeUniverse* other = multi[name];
			if(other == nullptr){
				ip.reflect();
				return true;
			}
			copySpace(other->getField(), src, size, runner.getUniverse().getField(), dest);
		} break;
		case 'G':{
			Vector delta = popVector(runner, 3);
			Vector pos = popVector(runner, 3);
			std::string name = popString(stack.top());
			FungeUniverse* other = multi[name];
			if(other == nullptr){
				ip.reflect();
				return true;
			}
			other->transferRunner(&runner);
			ip.setPos(pos);
			ip.setDelta(delta);
		}break;
		case 'J':{
			std::string name = popString(stack.top());
			FungeUniverse* other = multi[name];
			if(other == nullptr){
				ip.reflect();
				return true;
			}
			other->transferRunner(&runner);
		}break;
		case 'N':{
			pushString(stack.top(), universe.getName());
		} break;
		case 'P':{
			Vector size = popVector(runner);
			Vector src = popVector(runner);
			Vector dest = popVector(runner, 3);
			std::string name = popString(stack.top());
			FungeUniverse* other = multi[name];
			if(other == nullptr){
				ip.reflect();
				return true;
			}
			copySpace(runner.getUniverse().getField(), src, size, other->getField(), dest);
		} break;
		default:
			return false;
	}
	return true;
}

void FingerprintMVRS::copySpace(const Field& fsrc, const Vector& src, const Vector& sz, Field& fdest, const Vector& dest) const {
	VectorRange range(Vector{0}, sz);
	for(range.begin(); *range != range.end(); ++range){
		inst_t i = fsrc.get(src + *range);
		fdest.set(dest + *range, i);
	}
}

}
