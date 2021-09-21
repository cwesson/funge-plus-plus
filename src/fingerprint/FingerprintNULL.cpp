/**
 * @file FingerprintNULL.cpp
 * Null Fingerprint.
 * @author Conlan Wesson
 */

#include "FingerprintNULL.h"

namespace Funge {

FingerprintNULL::FingerprintNULL(FungeRunner& r) :
	Fingerprint(r,
			{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
			'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'})
{}

bool FingerprintNULL::execute(inst_t cmd){
	(void)cmd;
	ip.reflect();
	return true;
}

}
