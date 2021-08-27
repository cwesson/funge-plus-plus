/**
 * @file FingerprintHRTI.cpp
 * Referenced Cells Extension.
 * @author Conlan Wesson
 */

#include "FingerprintHRTI.h"
#include <cmath>

namespace Funge {

FingerprintHRTI::FingerprintHRTI(Field& f, InstructionPointer& i, StackStack& s) :
	Fingerprint(f, i, s, {'E', 'G', 'M', 'S', 'T'})
{}

bool FingerprintHRTI::execute(inst_t cmd){
	switch(cmd){
		case 'E':{
			hrti_mark = std::chrono::steady_clock::time_point();
		} break;
		case 'G':{
			double period = static_cast<double>(std::chrono::steady_clock::period::num) / static_cast<double>(std::chrono::steady_clock::period::den);
			stack.top().push(std::ceil(period * 1000000.0));
		} break;
		case 'M':{
			hrti_mark = std::chrono::steady_clock::now();
		} break;
		case 'S':{
			auto dur = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch());
			stack.top().push(dur.count() % static_cast<std::chrono::microseconds>(std::chrono::seconds(1)).count());
		} break;
		case 'T':{
			if(hrti_mark == std::chrono::steady_clock::time_point()){
				ip.reverse();
			}else{
				auto dur = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - hrti_mark);
				stack.top().push(dur.count());
			}
		} break;
		default:
			return false;
	}
	return true;
}

}
