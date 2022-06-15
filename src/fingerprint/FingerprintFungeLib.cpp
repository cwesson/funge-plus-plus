/**
 * @file FingerprintFungeLib.cpp
 * Dynamic Funge.
 * @author Conlan Wesson
 */

#include "FingerprintFungeLib.h"
#include "FungeMultiverse.h"

namespace Funge {

FingerprintFungeLib::FingerprintFungeLib(FungeRunner& r, std::istream& file, FungeConfig& cfg) :
	Fingerprint(r, {})
{
	dynamic = FungeMultiverse::getInstance().create(file, Field::FORMAT_FL, cfg);
	for(auto i : dynamic->getField().hasPlanes()){
		inst.push_back(i);
	}
}

bool FingerprintFungeLib::execute(inst_t cmd){
	StackStack& transstack = runner.getStack();
	dynamic->createRunner(Vector{0, 0, (cmd - 'A')}, Vector{1}, transstack);
	dynamic->wait();
	transstack.setRunner(runner);
	return true;
}

}
