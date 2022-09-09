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

FungeError FingerprintMVRS::execute(inst_t cmd){
	FungeError ret = ERROR_NONE;
	FungeMultiverse& multi = FungeMultiverse::getInstance();
	const FungeUniverse& universe = runner.getUniverse();
	switch(cmd){
		case 'B':{
			stack_t dim = stack.top().pop();
			stack_t lng = stack.top().pop();
			FungeMode flgs = static_cast<FungeMode>(stack.top().pop());
			std::string name = popString(stack.top());
			if(dim == 0){
				dim = runner.getUniverse().dimensions();
			}
			if(flgs == 0){
				flgs = runner.getMode();
			}else if((flgs & 0x1FF) != 0){
				ret = ERROR_UNSPEC;
				break;
			}
			FungeStandard stand;
			switch(lng){
				case 0:
					stand = runner.getUniverse().standard();
					break;
				case 1:
					stand = FUNGE_93;
					break;
				case 2:
					stand = FUNGE_98;
					break;
				default:
					ret = ERROR_UNSPEC;
					break;
			}
			if(ret == ERROR_NONE){
				FungeConfig config;
				config.name = name;
				config.dimensions = dim;
				config.standard = stand;
				config.mode = flgs;
				multi.create(config);
			}
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
				ret = ERROR_UNSPEC;
				break;
			}
			copySpace(other->getField(), src, size, runner.getUniverse().getField(), dest);
		} break;
		case 'G':{
			Vector delta = popVector(runner, 3);
			Vector pos = popVector(runner, 3);
			std::string name = popString(stack.top());
			FungeUniverse* other = multi[name];
			if(other == nullptr){
				ret = ERROR_UNSPEC;
				break;
			}
			other->transferRunner(&runner);
			ip.setPos(pos);
			ip.setDelta(delta);
		}break;
		case 'J':{
			std::string name = popString(stack.top());
			FungeUniverse* other = multi[name];
			if(other == nullptr){
				ret = ERROR_UNSPEC;
				break;
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
				ret = ERROR_UNSPEC;
				break;
			}
			copySpace(runner.getUniverse().getField(), src, size, other->getField(), dest);
		} break;
		default:
			ret = ERROR_UNIMP;
	}
	return ret;
}

void FingerprintMVRS::copySpace(const Field& fsrc, const Vector& src, const Vector& sz, Field& fdest, const Vector& dest) const {
	VectorRange range(Vector{0}, sz);
	for(range.begin(); *range != range.end(); ++range){
		inst_t i = fsrc.get(src + *range);
		fdest.put(dest + *range, i);
	}
}

}
