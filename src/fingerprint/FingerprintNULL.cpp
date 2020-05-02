/**
 * @file FingerprintNULL.h
 * Null Fingerprint.
 * @author Conlan Wesson
 */

#include "FingerprintNULL.h"

namespace Funge {

FingerprintNULL::FingerprintNULL(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s,
			{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
			'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'})
{}

bool FingerprintNULL::execute(inst_t cmd){
	if(cmd >= 'A' && cmd <= 'Z'){
		ip.reverse();
		return true;
	}
	return false;
}

}
