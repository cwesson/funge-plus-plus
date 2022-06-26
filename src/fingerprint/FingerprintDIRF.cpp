/**
 * @file FingerprintDIRF.h
 * Directory functions.
 * @author Conlan Wesson
 */

#include "FingerprintDIRF.h"
#include "FungeUtilities.h"
#include<filesystem>

namespace Funge {

FingerprintDIRF::FingerprintDIRF(FungeRunner& r) :
	Fingerprint(r, {'C', 'M', 'R'})
{}

FungeError FingerprintDIRF::execute(inst_t cmd){
	FungeError ret = ERROR_NONE;
	switch(cmd){
		case 'C':{
			std::filesystem::path dir = popString(runner.getStack().top());
			if(std::filesystem::exists(dir) && std::filesystem::is_directory(dir)){
				std::filesystem::current_path(dir);
			}else{
				ret = ERROR_UNSPEC;
			}
		} break;
		case 'M':{
			std::filesystem::path dir = popString(runner.getStack().top());
			std::filesystem::create_directory(dir);
		} break;
		case 'R':{
			std::filesystem::path dir = popString(runner.getStack().top());
			if(std::filesystem::exists(dir) && std::filesystem::is_directory(dir)){
				std::filesystem::remove(dir);
			}else{
				ret = ERROR_UNSPEC;
			}
		} break;
		default:
			ret = ERROR_UNIMP;
	}
	return ret;
}

}
