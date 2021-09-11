/**
 * @file FingerprintPERL.cpp
 * Generic Interface to the Perl Language.
 * @author Conlan Wesson
 */

#include "FingerprintPERL.h"
#include "FungeConfig.h"
#include "FungeUtilities.h"
#include <iomanip>

namespace Funge {

FingerprintPERL::FingerprintPERL(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s, {'E', 'I', 'S'})
{}

bool FingerprintPERL::execute(inst_t cmd){
	switch(cmd){
		case 'E':{
			if(funge_config.execute){
				int e = perl(popString(stack.top()));
				pushString(stack.top(), std::to_string(e));
			}else{
				ip.reflect();
			}
		} break;
		case 'I':{
			if(funge_config.execute){
				int e = perl(popString(stack.top()));
				stack.top().push(e);
			}else{
				ip.reflect();
			}
		} break;
		case 'S':{
			stack.top().push(1);
		} break;
		default:
			return false;
	}
	return true;
}

int FingerprintPERL::perl(std::string code){
	std::string cmd = std::string("exit(eval{") + code + std::string("})");
	std::stringstream sq;
	sq << std::quoted(cmd);
	cmd = std::string("perl -e ") + sq.str();
	return system(cmd.c_str()) >> 8;
}

}
