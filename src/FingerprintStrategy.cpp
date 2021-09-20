/**
 * @file FingerprintStrategy.cpp
 * Strategy for fingerprint commands.
 * @author Conlan Wesson
 */

#include "FingerprintStrategy.h"
#include "FungeConfig.h"
#include "FingerprintBASE.h"
#include "FingerprintBITW.h"
#include "FingerprintBOOL.h"
#include "FingerprintCPLI.h"
#include "FingerprintDBUG.h"
#include "FingerprintFIXP.h"
#include "FingerprintFloat.h"
#include "FingerprintFPRT.h"
#include "FingerprintFRTH.h"
#include "FingerprintHRTI.h"
#include "FingerprintJSTR.h"
#include "FingerprintLONG.h"
#include "FingerprintMODE.h"
#include "FingerprintMODU.h"
#include "FingerprintNFUN.h"
#include "FingerprintNULL.h"
#include "FingerprintORTH.h"
#include "FingerprintPERL.h"
#include "FingerprintREFC.h"
#include "FingerprintROMA.h"
#include "FingerprintSTRN.h"
#include "FingerprintSUBR.h"
#include "FingerprintTERM.h"
#include "FingerprintTOYS.h"

namespace Funge {

FingerprintStrategy::FingerprintStrategy(FungeRunner& r) :
	FungeStrategy(r),
	available(),
	loaded()
{
	available[0x42415345] = new FingerprintBASE(runner);
	available[0x42495457] = new FingerprintBITW(runner);
	available[0x424F4F4C] = new FingerprintBOOL(runner);
	available[0x43504C49] = new FingerprintCPLI(runner);
	available[0x44425547] = new FingerprintDBUG(runner);
	available[0x46495850] = new FingerprintFIXP(runner);
	available[0x46504450] = new FingerprintFloat<double>(runner);
	available[0x46505254] = new FingerprintFPRT(runner);
	available[0x46505350] = new FingerprintFloat<float>(runner);
	available[0x46525448] = new FingerprintFRTH(runner);
	available[0x48525449] = new FingerprintHRTI(runner);
	available[0x4A535452] = new FingerprintJSTR(runner);
	available[0x4C4F4E47] = new FingerprintLONG(runner);
	available[0x4D4F4445] = new FingerprintMODE(runner);
	available[0x4D4F4455] = new FingerprintMODU(runner);
	available[0x4E46554E] = new FingerprintNFUN(runner);
	available[0x4E554C4C] = new FingerprintNULL(runner);
	available[0x4F525448] = new FingerprintORTH(runner);
	available[0x5045524C] = new FingerprintPERL(runner);
	available[0x52454643] = new FingerprintREFC(runner);
	available[0x524F4D41] = new FingerprintROMA(runner);
	available[0x5354524E] = new FingerprintSTRN(runner);
	available[0x53554252] = new FingerprintSUBR(runner);
	available[0x5445524D] = new FingerprintTERM(runner);
	available[0x544f5953] = new FingerprintTOYS(runner);
	
	for(auto fing : funge_config.fingerprints){
		load(fing);
	}

	for(auto i : {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
				'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}){
		r.setSemantic(i, std::bind(&FingerprintStrategy::operator(), this, std::placeholders::_1));
	}
}

FingerprintStrategy::~FingerprintStrategy(){
	for(auto f : available){
		delete f.second;
	}
}

bool FingerprintStrategy::operator()(inst_t cmd){
	bool done = false;
	auto found = loaded.find(cmd);
	if(found != loaded.cend()){
		if(found->second.size() > 0){
			done = found->second.top()->execute(cmd);
		}
	}
	return done;
}

bool FingerprintStrategy::load(uint64_t fingerprint){
	auto found = available.find(fingerprint);
	if(found != available.cend()){
		for(auto i : found->second->instructions()){
			auto exist = loaded.find(i);
			if(exist == loaded.cend()){
				loaded[i] = std::stack<Fingerprint*>();
			}
			loaded[i].push(found->second);
		}
		found->second->activate();
		//std::cout << "Loaded 0x" << std::hex << fingerprint << std::dec << std::endl;
		return true;
	}
	return false;
}

bool FingerprintStrategy::unload(uint64_t fingerprint){
	auto found = available.find(fingerprint);
	if(found != available.cend()){
		for(auto i : found->second->instructions()){
			auto exist = loaded.find(i);
			if(exist != loaded.cend()){
				exist->second.pop();
			}
		}
		return true;
	}
	return false;
}

FungeStrategy* FingerprintStrategy::clone(FungeRunner& r) const{
	return new FingerprintStrategy(r);
}

}
