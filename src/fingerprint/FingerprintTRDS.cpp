/**
 * @file FingerprintTRDS.cpp
 * IP travel in time and space.
 * @author Conlan Wesson
 */

#include "FingerprintTRDS.h"
#include "FungeUniverse.h"
#include "FungeUtilities.h"

namespace Funge {

FingerprintTRDS::FingerprintTRDS(FungeRunner& r) :
	Fingerprint(r, {'C', 'D', 'E', 'G', 'I', 'J', 'P', 'R', 'S', 'T', 'U', 'V'}),
	space(),
	space_rel(NONE),
	time(0),
	time_rel(NONE),
	vec(),
	vec_rel(NONE),
	jump_space(),
	jump_time(0),
	jump_vec(),
	jumping(false)
{}

FungeError FingerprintTRDS::execute(inst_t cmd){
	switch(cmd){
		case 'C':{
			runner.getUniverse().unlock();
		} break;
		case 'D':{
			space = popVector(runner);
			space_rel = ABSOLUTE;
		} break;
		case 'E':{
			space = popVector(runner);
			space_rel = RELATIVE;
		} break;
		case 'G':{
			stack.top().push(runner.getUniverse().getAge());
		} break;
		case 'I':{
			space = jump_space;
			time = jump_time;
			space_rel = ABSOLUTE;
			time_rel = ABSOLUTE;
			vec = jump_vec;
			vec_rel = ABSOLUTE;
		} break;
		case 'J':{
			FungeError ret = ERROR_BLOCK;
			ssize_t current_time = runner.getUniverse().getAge();
			if(!jumping){
				jump_space = runner.getIP().getPos();
				jump_time = current_time;
				jump_vec = runner.getIP().getDelta();
				switch(space_rel){
					case NONE:
						space = jump_space;
						break;
					case ABSOLUTE:
						break;
					case RELATIVE:
						space += jump_space;
						space_rel = ABSOLUTE;
						break;
				}
				switch(time_rel){
					case NONE:
						time = jump_time;
						break;
					case ABSOLUTE:
						break;
					case RELATIVE:
						time += jump_time;
						time_rel = ABSOLUTE;
						break;
				}
				
				switch(vec_rel){
					case NONE:
						vec = jump_vec;
						break;
					case ABSOLUTE:
						break;
					case RELATIVE:
						break;
				}
				if(time_rel == RELATIVE){
					time += jump_time;
					time_rel = ABSOLUTE;
				}
				if(time > jump_time){
					// Jumping to future, just block
					ret = ERROR_BLOCK;
					jumping = true;
				}if(time < jump_time){
					// Jumping to past not supported
					ret = ERROR_UNSPEC;
				} // else jump to now
			}else if(time > current_time){
				// Waiting for universe to catchup
				ret =  ERROR_BLOCK;
			}else{
				// Jump complete
				jumping = false;
				runner.getIP().setPos(space);
				runner.getIP().setDelta(vec);
			}
			return ret;
		} break;
		case 'P':{
			stack.top().push(0);
		} break;
		case 'R':{
			space = {0};
			space_rel = NONE;
			time = 0;
			time_rel = NONE;
			vec = {0};
			vec_rel = NONE;
			jump_space = {0};
			jump_time = 0;
			jump_vec = {0};
		} break;
		case 'S':{
			runner.getUniverse().lock();
		} break;
		case 'T':{
			time = stack.top().pop();
			time_rel = ABSOLUTE;
		} break;
		case 'U':{
			time = stack.top().pop();
			time_rel = RELATIVE;
		} break;
		case 'V':{
			vec = popVector(runner);
			vec_rel = ABSOLUTE;
		} break;
		default:
			return ERROR_UNIMP;
	}
	return ERROR_NONE;
}

}
