/**
 * @file FingerprintPERL.cpp
 * Generic Interface to the Perl Language.
 * @author Conlan Wesson
 */

#include "FingerprintPERL.h"
#include "FungeUtilities.h"
#include "FungeUniverse.h"
#include <iomanip>

namespace Funge {

FingerprintPERL::FingerprintPERL(FungeRunner& r) :
	Fingerprint(r, {'E', 'I', 'S'})
{}

FungeError FingerprintPERL::execute(inst_t cmd){
	FungeError ret = ERROR_NONE;
	switch(cmd){
		case 'E':{
			if(runner.getUniverse().allowExecute()){
				int e = perl(popString(stack.top()));
				pushString(stack.top(), std::to_string(e));
			}else{
				ret = ERROR_UNSPEC;
			}
		} break;
		case 'I':{
			if(runner.getUniverse().allowExecute()){
				int e = perl(popString(stack.top()));
				stack.top().push(e);
			}else{
				ret = ERROR_UNSPEC;
			}
		} break;
		case 'S':{
			stack.top().push(1);
		} break;
		default:
			ret = ERROR_UNIMP;
	}
	return ret;
}

int FingerprintPERL::perl(const std::string& code){
	std::string cmd = std::string("exit(eval{") + code + std::string("})");
	std::stringstream sq;
	sq << std::quoted(cmd);
	cmd = std::string("perl -e ") + sq.str();
	return system(cmd.c_str()) >> 8;
}

}
