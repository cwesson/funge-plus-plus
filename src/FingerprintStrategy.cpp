/**
 * @file FingerprintStrategy.cpp
 * Strategy for fingerprint commands.
 * @author Conlan Wesson
 */

#include "FingerprintStrategy.h"
#include "FungeUniverse.h"
#include "FingerprintBASE.h"
#include "FingerprintBITW.h"
#include "FingerprintBOOL.h"
#include "FingerprintCPLI.h"
#include "FingerprintDBUG.h"
#include "FingerprintDIRF.h"
#include "FingerprintDynamic.h"
#include "FingerprintFING.h"
#include "FingerprintFIXP.h"
#include "FingerprintFloat.h"
#include "FingerprintFPRT.h"
#include "FingerprintFRTH.h"
#include "FingerprintFungeLib.h"
#include "FingerprintHRTI.h"
#include "FingerprintIIPC.h"
#include "FingerprintJSTR.h"
#include "FingerprintLONG.h"
#include "FingerprintMODE.h"
#include "FingerprintMODU.h"
#include "FingerprintMVRS.h"
#include "FingerprintNFUN.h"
#include "FingerprintORTH.h"
#include "FingerprintPERL.h"
#include "FingerprintREFC.h"
#include "FingerprintSTRN.h"
#include "FingerprintSUBR.h"
#include "FingerprintTOYS.h"
#include "FungeUniverse.h"
#include <filesystem>

namespace Funge {

FingerprintStrategy::FingerprintStrategy(FungeRunner& r) :
	FungeStrategy(r),
	loaded()
{
	for(auto fing : runner.getUniverse().fingerprints()){
		load(fing);
	}
}

FingerprintStrategy::FingerprintStrategy(const FingerprintStrategy& orig, FungeRunner& r) :
	FungeStrategy(r),
	loaded()
{
	for(auto i : orig.loaded){
		load(i);
	}
}

FingerprintStrategy::~FingerprintStrategy(){
	for(auto f : available){
		delete f.second;
	}
}

FungeError FingerprintStrategy::execute(Fingerprint* fing, inst_t i){
	return fing->execute(i);
}

Fingerprint* FingerprintStrategy::loadBuiltin(uint64_t fingerprint){
	Fingerprint* fing = nullptr;
	switch(fingerprint){
		case 0x42415345: fing = new FingerprintBASE(runner); break;
		case 0x42495457: fing = new FingerprintBITW(runner); break;
		case 0x424F4F4C: fing = new FingerprintBOOL(runner); break;
		case 0x43504C49: fing = new FingerprintCPLI(runner); break;
		case 0x44425547: fing = new FingerprintDBUG(runner); break;
		case 0x44495246: fing = new FingerprintDIRF(runner); break;
		case 0x46494e47: fing = new FingerprintFING(runner); break;
		case 0x46495850: fing = new FingerprintFIXP(runner); break;
		case 0x46504450: fing = new FingerprintFloat<double>(runner); break;
		case 0x46505254: fing = new FingerprintFPRT(runner); break;
		case 0x46505350: fing = new FingerprintFloat<float>(runner); break;
		case 0x46525448: fing = new FingerprintFRTH(runner); break;
		case 0x48525449: fing = new FingerprintHRTI(runner); break;
		case 0x49495043: fing = new FingerprintIIPC(runner); break;
		case 0x4A535452: fing = new FingerprintJSTR(runner); break;
		case 0x4C4F4E47: fing = new FingerprintLONG(runner); break;
		case 0x4D4F4445: fing = new FingerprintMODE(runner); break;
		case 0x4D4F4455: fing = new FingerprintMODU(runner); break;
		case 0x4D565253: fing = new FingerprintMVRS(runner); break;
		case 0x4E46554E: fing = new FingerprintNFUN(runner); break;
		case 0x4F525448: fing = new FingerprintORTH(runner); break;
		case 0x5045524C: fing = new FingerprintPERL(runner); break;
		case 0x52454643: fing = new FingerprintREFC(runner); break;
		case 0x5354524E: fing = new FingerprintSTRN(runner); break;
		case 0x53554252: fing = new FingerprintSUBR(runner); break;
		case 0x544F5953: fing = new FingerprintTOYS(runner); break;
		case FingerprintDynamic::ID:
			if(runner.getUniverse().getCreator() != nullptr){
				fing = new FingerprintDynamic(runner, runner.getUniverse().getCreator());
			}
			break;
		default: break;
	}

	return fing;
}

Fingerprint* FingerprintStrategy::loadFL(uint64_t fingerprint){
	std::string str(intToStr(fingerprint));
	return FingerprintFungeLib::factory(runner, str);
}

bool FingerprintStrategy::load(uint64_t fingerprint){
	auto found = available.find(fingerprint);
	Fingerprint* fing = nullptr;
	if(found == available.cend()){
		fing = loadFL(fingerprint);
		if(fing == nullptr){
			fing = loadBuiltin(fingerprint);
		}
	}else{
		fing = found->second;
	}

	if(fing != nullptr){
		available[fingerprint] = fing;
		loaded.push_back(fingerprint);
		for(auto i : fing->instructions()){
			runner.pushSemantic(i, std::bind(&FingerprintStrategy::execute, this, fing, i));
		}
		fing->activate();
		//std::cout << "Loaded 0x" << std::hex << fingerprint << std::dec << std::endl;
		return true;
	}

	return false;
}

bool FingerprintStrategy::unload(uint64_t fingerprint){
	auto found = available.find(fingerprint);
	if(found != available.cend()){
		for(auto i : found->second->instructions()){
			runner.popSemantic(i);
		}
		for(auto listed = loaded.rbegin(); listed != loaded.rend(); ++listed){
			if(*listed == fingerprint){
				loaded.erase((listed+1).base());
				break;
			}
		}
		return true;
	}
	return false;
}

FungeStrategy* FingerprintStrategy::clone(FungeRunner& r) const{
	return new FingerprintStrategy(*this, r);
}

std::string FingerprintStrategy::intToStr(uint64_t i){
	std::string str;
	while(i > 0){
		char c = i & 0xFF;
		str = c + str;
		i >>= 8;
	}
	return str;
}

}
