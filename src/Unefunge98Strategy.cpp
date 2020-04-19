/**
 * @file Unefunge98Strategy.cpp
 * Strategy for Unefunge-98 commands.
 * @author Conlan Wesson
 */

#include "Unefunge98Strategy.h"
#include "FungeRunner.h"
#include "FungeConfig.h"
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
				if(funge_config.concurrent){
					FungeRunner* runner = new FungeRunner(field, stack, ip);
					(void)runner;
				}else{
					std::cerr << "Unimplemented instruction " << static_cast<int>(cmd) << " \'" << static_cast<char>(cmd) << "\' at " << ip << "." << std::endl;
					std::cerr << "Run without -fno-concurrent to enable concurrency." << std::endl;
					ip.reverse();
				}
			} break;
			
			case 'x':{
				size_t s = funge_config.dimensions;
				Vector v;
				for(size_t i = s; i > 0; --i){
					v.set(i-1, stack.top().pop());
				}
				ip.setDelta(v);
			} break;
			
			case '{':{
				stack_t n = std::abs(stack.top().pop());
				stack.push();
				stack_t trans[n];
				for(stack_t i = 0; i < n; ++i){
					trans[i] = stack.second().pop();
				}
				for(stack_t i = n; i > 0; --i){
					stack.top().push(trans[i-1]);
				}
				const Vector& storage = ip.getStorage();
				size_t s = funge_config.dimensions;
				for(size_t i = 0; i < s; ++i){
					stack.second().push(storage[i]);
				}
				ip.setStorage(ip.getPos()+ip.getDelta());
			} break;
			case '}':{
				if(stack.size() > 1){
					stack_t n = std::abs(stack.top().pop());
					size_t s = funge_config.dimensions;
					Vector v;
					for(size_t i = s; i > 0; --i){
						v.set(i-1, stack.second().pop());
					}
					ip.setStorage(v);
					stack_t trans[n];
					for(stack_t i = 0; i < n; ++i){
						trans[i] = stack.top().pop();
					}
					for(stack_t i = n; i > 0; --i){
						stack.second().push(trans[i-1]);
					}
					stack.pop();
				}else{
					ip.reverse();
				}
			} break;
			case 'u':{
				if(stack.size() > 1){
					stack_t n = stack.top().pop();
					for(stack_t i = 0; i < n; ++i){
						stack_t trans = stack.second().pop();
						stack.top().push(trans);
					}
				}else{
					ip.reverse();
				}
			} break;
			
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
	size_t s = funge_config.dimensions;
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
	const Vector& vs = ip.getStorage();
	for(size_t i = 0; i < s; ++i){
		stack.top().push(vs[i]);
	}
	// Delta vector
	const Vector& vd = ip.getDelta();
	for(size_t i = 0; i < s; ++i){
		stack.top().push(vd[i]);
	}
	// Current position
	const Vector& vp = ip.getPos();
	for(size_t i = 0; i < s; ++i){
		stack.top().push(vp[i]);
	}
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
