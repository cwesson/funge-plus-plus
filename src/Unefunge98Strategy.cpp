/**
 * @file Unefunge98Strategy.cpp
 * Strategy for Unefunge-98 commands.
 * @author Conlan Wesson
 */

#include "Unefunge98Strategy.h"
#include "FungeRunner.h"
#include <iostream>
#include <thread>
#include <ctime>

namespace Funge {


Unefunge98Strategy::Unefunge98Strategy(Field& f, InstructionPointer& i, StackStack& s) :
	Unefunge93Strategy(f, i, s)
{
	
}

bool Unefunge98Strategy::execute(inst_t cmd){
	if(cmd >= 'a' && cmd <= 'f'){
		stack.top().push(cmd-'a'+10);
	}else if(cmd >= 'A' && cmd <= 'Z'){
		execute('r');
	}else{
		switch(cmd){
			case 'z': break; //No-op
			case '\'':{
				ip.next();
				stack.top().push((int)ip.get());
			} break;
			case ';':{
				do{
					ip.next();
				}while(ip.get() != ';');
			} break;
			case 'j':{
				int j = stack.top().pop();
				for(int i = 0; i < j; i++){
					ip.next();
				}
			} break;
			case 'k':{
				ip.next();
				char c = ip.get();
				int k = stack.top().pop();
				for(int i = 0; i < k; i++){
					execute(c);
				}
			} break;
			case 'n':
				stack.top().clear();
				break;
			case 'q':{
				int r = stack.top().pop();
				exit(r);
			} break;
			case 'r':
				ip.reverse();
				break;
			case 's':{
				ip.next();
				ip.set((char)(int)stack.top().pop());
			} break;
			
			case 't':{
				FungeRunner* runner = new FungeRunner(field, stack, ip);
				(void)runner;
			} break;
			
			case 'x':{
				int s = field.dimensions();
				Vector v;
				for(int i = s-1; i >= 0; i--){
					v.set(i, stack.top().pop());
				}
				ip.setDelta(v);
				break;
			}
			
			case 'y':
				pushSysInfo(stack.top().pop());
				break;
			
			default:
				return Unefunge93Strategy::execute(cmd);
		}
	}
	return true;
}

void Unefunge98Strategy::pushSysInfo(int num){
	int pushes = 26;
	// ENV variables
	stack.top().push(0);
	stack.top().push(0);
	// ARGV
	stack.top().push(0);
	stack.top().push(0);
	// Size of stacks
	for(size_t i = stack.size(); i > 0; --i){
		stack.top().push(stack.at(i-1).size());
		pushes++;
	}
	// Number of stacks
	stack.top().push(stack.size());
	// Time
	std::time_t now = std::time(nullptr);
	std::tm* dt = std::localtime(&now);
	stack.top().push(dt->tm_hour*256*256 + dt->tm_min*256 + dt->tm_sec);
	// Date
	stack.top().push((dt->tm_year-1900)*256*256 + (dt->tm_mon+1)*256 + dt->tm_mday);
	// Greatest non-space
	stack.top().push(field.max(0));
	stack.top().push(field.max(1));
	// Least non-space
	stack.top().push(field.min(0));
	stack.top().push(field.min(1));
	// Storage Offset
	stack.top().push(0);
	stack.top().push(0);
	// Delta vector
	stack.top().push(ip.getDelta().get(0));
	stack.top().push(ip.getDelta().get(1));
	// Current position
	stack.top().push(ip.getPos().get(0));
	stack.top().push(ip.getPos().get(1));
	// Team number
	stack.top().push(0);
	// Thread ID
	std::hash<std::thread::id> hasher;
	stack.top().push(hasher(std::this_thread::get_id()));
	// Scalars per vector
	stack.top().push(2);
	// Path separator
	stack.top().push('/');
	// Operating Paradigm
	stack.top().push(0);
	// Version Number
	stack.top().push(1);
	// Handprint
	stack.top().push(0xC01AE550);
	// Bytes per cell
	stack.top().push(sizeof(stack_t));
	// Flags
	stack.top().push(0x01);
	if(num > 0){
		int val = 0;
		for(int i = 1; i <= num; i++){
			val = stack.top().pop();
		}
		for(int i = num; i < pushes; i++){
			stack.top().pop();
		}
		stack.top().push(val);
	}
}

}
