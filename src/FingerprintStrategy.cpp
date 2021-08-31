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
#include "FingerprintTERM.h"
#include "FingerprintTOYS.h"

namespace Funge {

FingerprintStrategy::FingerprintStrategy(Field& f, InstructionPointer& i, StackStack& s, FungeRunner& r) :
	FungeStrategy(f, i, s, r,
			{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
			'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}),
	available(),
	loaded()
{
	available[0x42415345] = new FingerprintBASE(f, i, s);
	available[0x42495457] = new FingerprintBITW(f, i, s);
	available[0x424F4F4C] = new FingerprintBOOL(f, i, s);
	available[0x43504C49] = new FingerprintCPLI(f, i, s);
	available[0x44425547] = new FingerprintDBUG(f, i, s);
	available[0x46495850] = new FingerprintFIXP(f, i, s);
	available[0x46504450] = new FingerprintFloat<double>(f, i, s);
	available[0x46505254] = new FingerprintFPRT(f, i, s);
	available[0x46505350] = new FingerprintFloat<float>(f, i, s);
	available[0x46525448] = new FingerprintFRTH(f, i, s);
	available[0x48525449] = new FingerprintHRTI(f, i, s);
	available[0x4A535452] = new FingerprintJSTR(f, i, s);
	available[0x4C4F4E47] = new FingerprintLONG(f, i, s);
	available[0x4D4F4445] = new FingerprintMODE(f, i, s);
	available[0x4D4F4455] = new FingerprintMODU(f, i, s);
	available[0x4E46554E] = new FingerprintNFUN(f, i, s);
	available[0x4E554C4C] = new FingerprintNULL(f, i, s);
	available[0x4F525448] = new FingerprintORTH(f, i, s);
	available[0x5045524C] = new FingerprintPERL(f, i, s);
	available[0x52454643] = new FingerprintREFC(f, i, s);
	available[0x524F4D41] = new FingerprintROMA(f, i, s);
	available[0x5445524D] = new FingerprintTERM(f, i, s);
	available[0x544f5953] = new FingerprintTOYS(f, i, s);
	
	for(auto fing : funge_config.fingerprints){
		load(fing);
	}
}

FingerprintStrategy::~FingerprintStrategy(){
	for(auto f : available){
		delete f.second;
	}
}

bool FingerprintStrategy::execute(inst_t cmd){
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

}
