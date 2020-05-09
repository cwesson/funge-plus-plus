/**
 * @file Unefunge98Strategy.cpp
 * Strategy for Unefunge-98 commands.
 * @author Conlan Wesson
 */

#include "Unefunge98Strategy.h"
#include "FungeRunner.h"
#include "FungeUtilities.h"
#include "FungeConfig.h"
#include "FungeVersion.h"
#include <thread>
#include <fstream>
#include <ctime>

namespace Funge {


Unefunge98Strategy::Unefunge98Strategy(Field& f, InstructionPointer& i, StackStack& s, FungeState& t) :
	FungeStrategy(f, i, s, t,
			{'a', 'b', 'c', 'd', 'e', 'f', 'j', 'i', 'k', 'n', 'o', 'q', 'r', 's', 't', 'u', 'x', 'y', 'z',
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
			'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
			'\'', ';', '{', '}', '=', '(', ')'}),
	finger(f, i, s, t)
{
	
}

bool Unefunge98Strategy::execute(inst_t cmd){
	if(cmd >= 'a' && cmd <= 'f'){
		stack.top().push(cmd-'a'+10);
	}else if(cmd >= 'A' && cmd <= 'Z'){
		return finger.execute(cmd);
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
				ip.next();
				state.execute(ip.get());
			} break;
			case 'j':{
				int j = stack.top().pop();
				if(j < 0){
					ip.reverse();
				}
				for(int i = 0; i < std::abs(j); i++){
					ip.next();
				}
				if(j < 0){
					ip.reverse();
				}
			} break;
			case 'k':{
				Vector v = ip.getPos();
				ip.next();
				char c = field.get(ip.getPos());
				while(c == ' ' || c == ';'){
					c = field.get(ip.getPos());
					ip.next();
				}
				ip.setPos(v);
				int k = stack.top().pop();
				for(int i = 0; i < k; i++){
					state.execute(c);
				}
				if(k == 0){
					ip.next();
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
					std::cerr << "Run with -fconcurrent to enable concurrency." << std::endl;
					ip.reverse();
				}
			} break;
			
			case 'x':{
				Vector v = popVector(stack.top());
				ip.setDelta(v);
			} break;
			
			case '{':{
				const stack_t n = stack.top().pop();
				stack.push();
				if(n > 0){
					stack_t trans[n];
					for(stack_t i = 0; i < n; ++i){
						trans[i] = stack.second().pop();
					}
					for(stack_t i = n; i > 0; --i){
						stack.top().push(trans[i-1]);
					}
				}else{
					for(stack_t i = 0; i < std::abs(n); ++i){
						stack.second().push(0);
					}
				}
				const Vector& storage = ip.getStorage();
				pushVector(stack.second(), storage);
				ip.setStorage(ip.getPos()+ip.getDelta());
			} break;
			case '}':{
				if(stack.size() > 1){
					const stack_t n = stack.top().pop();
					Vector v = popVector(stack.second());
					ip.setStorage(v);
					if(n > 0){
						stack_t trans[n];
						for(stack_t i = 0; i < n; ++i){
							trans[i] = stack.top().pop();
						}
						for(stack_t i = n; i > 0; --i){
							stack.second().push(trans[i-1]);
						}
					}else{
						for(stack_t i = 0; i < std::abs(n); ++i){
							stack.second().pop();
						}
					}
					stack.pop();
				}else{
					ip.reverse();
				}
			} break;
			case 'u':{
				if(stack.size() > 1){
					const stack_t n = stack.top().pop();
					if(n > 0){
						for(stack_t i = 0; i < n; ++i){
							stack_t trans = stack.second().pop();
							stack.top().push(trans);
						}
					}else{
						for(stack_t i = 0; i < -n; ++i){
							stack_t trans = stack.top().pop();
							stack.second().push(trans);
						}
					}
				}else{
					ip.reverse();
				}
			} break;
			
			case '=':{
				if(funge_config.execute){
					std::string sys = popString(stack.top());
					int code = system(sys.c_str());
					stack.top().push(code);
				}else{
					std::cerr << "Unimplemented instruction " << static_cast<int>(cmd) << " \'" << static_cast<char>(cmd) << "\' at " << ip << "." << std::endl;
					std::cerr << "Run with -fexecute to enable execution." << std::endl;
					ip.reverse();
				}
			} break;
			
			case 'i':{
				if(funge_config.filesystem){
					std::string filepath = popString(stack.top());
					stack_t flags = stack.top().pop();
					Vector va = popVector(stack.top());
					va += ip.getStorage();
					std::ifstream file(filepath);
					if(!file.fail()){
						Vector vb = field.parse(va, file, !!(flags & FILE_IN_BINARY));
						pushVector(stack.top(), vb);
						pushVector(stack.top(), va);
					}else{
						ip.reverse();
					}
				}else{
					std::cerr << "Unimplemented instruction " << static_cast<int>(cmd) << " \'" << static_cast<char>(cmd) << "\' at " << ip << "." << std::endl;
					std::cerr << "Run with -ffilesystem to enable execution." << std::endl;
					ip.reverse();
				}
			} break;
			case 'o':{
				if(funge_config.filesystem){
					std::string filepath = popString(stack.top());
					stack_t flags = stack.top().pop();
					std::ignore = flags;
					Vector va = popVector(stack.top());
					va += ip.getStorage();
					Vector vb = popVector(stack.top());
					std::ofstream file(filepath);
					if(!file.fail()){
						field.dump(va, vb, file, !(flags & FILE_OUT_TEXT));
					}else{
						ip.reverse();
					}
				}else{
					std::cerr << "Unimplemented instruction " << static_cast<int>(cmd) << " \'" << static_cast<char>(cmd) << "\' at " << ip << "." << std::endl;
					std::cerr << "Run with -ffilesystem to enable execution." << std::endl;
					ip.reverse();
				}
			} break;
			
			case '(':{
				if(funge_config.fingerprint){
					const stack_t count = stack.top().pop();
					uint64_t fingerprint = 0;
					for(stack_t i = 0; i < count; ++i){
						fingerprint = (fingerprint << 8) + stack.top().pop();
					}
					if(finger.load(fingerprint)){
						stack.top().push(fingerprint);
						stack.top().push(1);
					}else{
						ip.reverse();
					}
				}else{
					std::cerr << "Unimplemented instruction " << static_cast<int>(cmd) << " \'" << static_cast<char>(cmd) << "\' at " << ip << "." << std::endl;
					std::cerr << "Run with -ffingerprint to enable fingerprints." << std::endl;
					ip.reverse();
				}
			} break;
			case ')':{
				if(funge_config.fingerprint){
					const stack_t count = stack.top().pop();
					uint64_t fingerprint = 0;
					for(stack_t i = 0; i < count; ++i){
						fingerprint = (fingerprint << 8) + stack.top().pop();
					}
					if(!finger.unload(fingerprint)){
						ip.reverse();
					}
				}else{
					std::cerr << "Unimplemented instruction " << static_cast<int>(cmd) << " \'" << static_cast<char>(cmd) << "\' at " << ip << "." << std::endl;
					std::cerr << "Run with -ffingerprint to enable fingerprints." << std::endl;
					ip.reverse();
				}
			} break;
			
			case 'y':
				pushSysInfo(stack.top().pop());
				break;
			
			default:
				return false;
		}
	}
	return true;
}

void Unefunge98Strategy::pushSysInfo(int num){
	const size_t s = funge_config.dimensions;
	const stack_t tsize = stack.top().size();
	int pushes = 0;
	// ENV variables
	pushes += stack.top().push(0);
	pushes += stack.top().push(0);
	if(funge_config.env.size() > 0){
		for(auto arg = funge_config.env.crbegin(); arg != funge_config.env.crend(); ++arg){
			pushes += pushString(stack.top(), *arg);
		}
	}
	// ARGV
	pushes += stack.top().push(0);
	pushes += stack.top().push(0);
	if(funge_config.args.size() > 0){
		for(auto arg = funge_config.args.crbegin(); arg != funge_config.args.crend(); ++arg){
			pushes += pushString(stack.top(), *arg);
		}
	}
	// Size of stacks
	for(size_t i = stack.size(); i > 1; --i){
		pushes += stack.top().push(stack.at(i-1).size());
	}
	pushes += stack.top().push(tsize);
	// Number of stacks
	pushes += stack.top().push(stack.size());
	// Time
	std::time_t now = std::time(nullptr);
	std::tm* dt = std::localtime(&now);
	pushes += stack.top().push((dt->tm_hour << 16) + (dt->tm_min << 8) + dt->tm_sec);
	// Date
	pushes += stack.top().push((dt->tm_year << 16) + ((dt->tm_mon+1) << 8) + dt->tm_mday);
	// Greatest non-space
	for(size_t i = 0; i < s; ++i){
		pushes += stack.top().push(field.max(i)-field.min(i));
	}
	// Least non-space
	for(size_t i = 0; i < s; ++i){
		pushes += stack.top().push(field.min(i));
	}
	// Storage Offset
	pushes += pushVector(stack.top(), ip.getStorage());
	// Delta vector
	pushes += pushVector(stack.top(), ip.getDelta());
	// Current position
	pushes += pushVector(stack.top(), ip.getPos());
	// Team number
	pushes += stack.top().push(0);
	// Thread ID
	pushes += stack.top().push(ip.getID());
	// Scalars per vector
	pushes += stack.top().push(funge_config.dimensions);
	// Path separator
	pushes += stack.top().push('/');
	// Operating Paradigm
	pushes += stack.top().push(OP_SYSTEM);
	// Version Number
	pushes += stack.top().push(FUNGE_VERSION);
	// Handprint
	pushes += stack.top().push(FUNGE_HANDPRINT);
	// Bytes per cell
	pushes += stack.top().push(sizeof(stack_t));
	// Flags
	stack_t flags = ENV_UNBUFFERED_IO;
	if(funge_config.concurrent){
		flags |= ENV_CONCURRENT;
	}
	if(funge_config.execute){
		flags |= ENV_EXECUTE;
	}
	if(funge_config.filesystem){
		flags |= ENV_FILE_IN | ENV_FILE_OUT;
	}
	pushes += stack.top().push(flags);
	if(num > 0){
		stack_t val = stack.top().get(num);
		for(int i = 0; i < pushes; i++){
			stack.top().pop();
		}
		stack.top().push(val);
	}
}

}
