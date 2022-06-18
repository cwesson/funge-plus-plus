/**
 * @file FingerprintFungeLib.cpp
 * Dynamic Funge.
 * @author Conlan Wesson
 */

#include "FingerprintFungeLib.h"
#include "FungeMultiverse.h"
#include "FingerprintDynamic.h"
#include <filesystem>
#include <fstream>

namespace Funge {

FingerprintFungeLib::FingerprintFungeLib(FungeRunner& r, std::istream& file, FungeConfig& cfg) :
	Fingerprint(r, {})
{
	dynamic = FungeMultiverse::getInstance().create(file, Field::FORMAT_FL, cfg, &r);
	for(auto i : dynamic->getField().hasPlanes()){
		inst.push_back(i);
	}
}

FingerprintFungeLib* FingerprintFungeLib::factory(FungeRunner& r, std::string& name){
	std::filesystem::path fl = std::filesystem::canonical("/proc/self/exe").parent_path();
	fl /= "..";
	fl /= "fing";
	fl /= name + ".fl";

	FingerprintFungeLib* fing = nullptr;
	if(std::filesystem::exists(fl)){
		std::ifstream stream(fl);
		if(stream.fail()){
			std::cerr << "Failed to open " << fl << std::endl;
			return nullptr;
		}

		FungeConfig config;
		config.name = std::filesystem::canonical(fl);
		if(r.isMode(FUNGE_MODE_DEBUG)){
			config.mode |= FUNGE_MODE_DEBUG;
		}
		config.fingerprints.push_back(FingerprintDynamic::ID);

		fing = new FingerprintFungeLib(r, stream, config);
	}
	return fing;
}

bool FingerprintFungeLib::execute(inst_t cmd){
	dynamic->createRunner(Vector{0, 0, (cmd - 'A')}, Vector{1}, runner);
	dynamic->wait();
	StackStack& transstack = runner.getStack();
	transstack.setRunner(runner);
	return true;
}

}
