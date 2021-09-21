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


Unefunge98Strategy::Unefunge98Strategy(FungeRunner& r) :
	FungeStrategy(r),
	finger(r)
{
	r.setSemantic('a', std::bind(&Unefunge98Strategy::instructionPush, this, std::placeholders::_1, 0xA));
	r.setSemantic('b', std::bind(&Unefunge98Strategy::instructionPush, this, std::placeholders::_1, 0xB));
	r.setSemantic('c', std::bind(&Unefunge98Strategy::instructionPush, this, std::placeholders::_1, 0xC));
	r.setSemantic('d', std::bind(&Unefunge98Strategy::instructionPush, this, std::placeholders::_1, 0xD));
	r.setSemantic('e', std::bind(&Unefunge98Strategy::instructionPush, this, std::placeholders::_1, 0xE));
	r.setSemantic('f', std::bind(&Unefunge98Strategy::instructionPush, this, std::placeholders::_1, 0xF));
	r.setSemantic('y', std::bind(&Unefunge98Strategy::instructionSysInfo, this, std::placeholders::_1));
	r.setSemantic('z', std::bind(&Unefunge98Strategy::instructionNoop, this, std::placeholders::_1));
	// Flow Control
	r.setSemantic(';', std::bind(&Unefunge98Strategy::instructionJumpOver, this, std::placeholders::_1));
	r.setSemantic('j', std::bind(&Unefunge98Strategy::instructionJumpForward, this, std::placeholders::_1));
	r.setSemantic('r', std::bind(&Unefunge98Strategy::instructionReflect, this, std::placeholders::_1));
	r.setSemantic('x', std::bind(&Unefunge98Strategy::instructionAbsolute, this, std::placeholders::_1));
	r.setSemantic('k', std::bind(&Unefunge98Strategy::instructionIterate, this, std::placeholders::_1));
	r.setSemantic('q', std::bind(&Unefunge98Strategy::instructionQuit, this, std::placeholders::_1));
	r.setSemantic('t', std::bind(&Unefunge98Strategy::instructionThread, this, std::placeholders::_1));
	// Stack Operations
	r.setSemantic('n', std::bind(&Unefunge98Strategy::instructionClear, this, std::placeholders::_1));
	r.setSemantic('u', std::bind(&Unefunge98Strategy::instructionUnder, this, std::placeholders::_1));
	r.setSemantic('{', std::bind(&Unefunge98Strategy::instructionBegin, this, std::placeholders::_1));
	r.setSemantic('}', std::bind(&Unefunge98Strategy::instructionEnd, this, std::placeholders::_1));
	// I/O
	r.setSemantic('i', std::bind(&Unefunge98Strategy::instructionFileIn, this, std::placeholders::_1));
	r.setSemantic('o', std::bind(&Unefunge98Strategy::instructionFileOut, this, std::placeholders::_1));
	r.setSemantic('=', std::bind(&Unefunge98Strategy::instructionExecute, this, std::placeholders::_1));
	// Self-Modifying
	r.setSemantic('\'', std::bind(&Unefunge98Strategy::instructionFetch, this, std::placeholders::_1));
	r.setSemantic('s', std::bind(&Unefunge98Strategy::instructionStore, this, std::placeholders::_1));
	// Fingerprints
	r.setSemantic('(', std::bind(&Unefunge98Strategy::instructionLoad, this, std::placeholders::_1));
	r.setSemantic(')', std::bind(&Unefunge98Strategy::instructionUnload, this, std::placeholders::_1));
}

bool Unefunge98Strategy::instructionPush(inst_t i, int n){
	(void)i;
	stack.top().push(n);
	return true;
}

bool Unefunge98Strategy::instructionSysInfo(inst_t i){
	(void)i;
	pushSysInfo(stack.top().pop());
	return true;
}

bool Unefunge98Strategy::instructionNoop(inst_t i){
	(void)i;
	return true;
}

bool Unefunge98Strategy::instructionJumpOver(inst_t i){
	(void)i;
	do{
		ip.next();
	}while(ip.get() != ';');
	do{
		ip.next();
	}while(ip.get() == ' ');
	runner.execute(ip.get());
	return true;
}

bool Unefunge98Strategy::instructionJumpForward(inst_t i){
	(void)i;
	int j = stack.top().pop();
	if(j < 0){
		ip.reflect();
	}
	for(int i = 0; i < std::abs(j); i++){
		ip.next();
	}
	if(j < 0){
		ip.reflect();
	}
	return true;
}

bool Unefunge98Strategy::instructionReflect(inst_t i){
	(void)i;
	ip.reflect();
	return true;
}

bool Unefunge98Strategy::instructionAbsolute(inst_t i){
	(void)i;
	Vector v = popVector(stack.top());
	ip.setDelta(v);
	return true;
}

bool Unefunge98Strategy::instructionIterate(inst_t i){
	(void)i;
	Vector v = ip.getPos();
	ip.next();
	char c = field.get(ip.getPos());
	while(c == ' ' || c == ';'){
		if(c == ';'){
			do{
				ip.next();
				c = ip.get();
			}while(c != ';');
			ip.next();
			c = ip.get();
		}else{
			ip.next();
			c = ip.get();
		}
	}
	ip.setPos(v);
	int k = stack.top().pop();
	for(int i = 0; i < k; i++){
		runner.execute(c);
	}
	if(k == 0){
		ip.next();
	}
	return true;
}

bool Unefunge98Strategy::instructionQuit(inst_t i){
	(void)i;
	int r = stack.top().pop();
	exit(r);
	// Unreachable
	return true;
}

bool Unefunge98Strategy::instructionThread(inst_t i){
	if(funge_config.concurrent){
		runner.getUniverse().cloneRunner(runner);
	}else{
		std::cerr << "Unimplemented instruction " << static_cast<int>(i) << " \'" << static_cast<char>(i) << "\' at " << ip << "." << std::endl;
		std::cerr << "Run with -fconcurrent to enable concurrency." << std::endl;
		ip.reflect();
	}
	return true;
}

bool Unefunge98Strategy::instructionClear(inst_t i){
	(void)i;
	stack.top().clear();
	return true;
}

bool Unefunge98Strategy::instructionUnder(inst_t i){
	(void)i;
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
		ip.reflect();
	}
	return true;
}

bool Unefunge98Strategy::instructionBegin(inst_t i){
	(void)i;
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
	
	if(funge_config.switchmode){
		ip.set('}');
	}
	return true;
}

bool Unefunge98Strategy::instructionEnd(inst_t i){
	(void)i;
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
		ip.reflect();
	}
	
	if(funge_config.switchmode){
		ip.set('{');
	}
	return true;
}

bool Unefunge98Strategy::instructionFileIn(inst_t i){
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
			ip.reflect();
		}
	}else{
		std::cerr << "Unimplemented instruction " << static_cast<int>(i) << " \'" << static_cast<char>(i) << "\' at " << ip << "." << std::endl;
		std::cerr << "Run with -ffilesystem to enable execution." << std::endl;
		ip.reflect();
	}
	return true;
}

bool Unefunge98Strategy::instructionFileOut(inst_t i){
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
			ip.reflect();
		}
	}else{
		std::cerr << "Unimplemented instruction " << static_cast<int>(i) << " \'" << static_cast<char>(i) << "\' at " << ip << "." << std::endl;
		std::cerr << "Run with -ffilesystem to enable execution." << std::endl;
		ip.reflect();
	}
	return true;
}

bool Unefunge98Strategy::instructionExecute(inst_t i){
	if(funge_config.execute){
		std::string sys = popString(stack.top());
		int code = system(sys.c_str());
		stack.top().push(code);
	}else{
		std::cerr << "Unimplemented instruction " << static_cast<int>(i) << " \'" << static_cast<char>(i) << "\' at " << ip << "." << std::endl;
		std::cerr << "Run with -fexecute to enable execution." << std::endl;
		ip.reflect();
	}
	return true;
}

bool Unefunge98Strategy::instructionFetch(inst_t i){
	(void)i;
	ip.next();
	stack.top().push((int)ip.get());
	return true;
}

bool Unefunge98Strategy::instructionStore(inst_t i){
	(void)i;
	ip.next();
	ip.set((char)(int)stack.top().pop());
	return true;
}

bool Unefunge98Strategy::instructionLoad(inst_t i){
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
			ip.reflect();
		}
	}else{
		std::cerr << "Unimplemented instruction " << static_cast<int>(i) << " \'" << static_cast<char>(i) << "\' at " << ip << "." << std::endl;
		std::cerr << "Run with -ffingerprint to enable fingerprints." << std::endl;
		ip.reflect();
	}
	
	if(funge_config.switchmode){
		ip.set(')');
	}
	return true;
}

bool Unefunge98Strategy::instructionUnload(inst_t i){
	if(funge_config.fingerprint){
		const stack_t count = stack.top().pop();
		uint64_t fingerprint = 0;
		for(stack_t i = 0; i < count; ++i){
			fingerprint = (fingerprint << 8) + stack.top().pop();
		}
		if(!finger.unload(fingerprint)){
			ip.reflect();
		}
	}else{
		std::cerr << "Unimplemented instruction " << static_cast<int>(i) << " \'" << static_cast<char>(i) << "\' at " << ip << "." << std::endl;
		std::cerr << "Run with -ffingerprint to enable fingerprints." << std::endl;
		ip.reflect();
	}
	
	if(funge_config.switchmode){
		ip.set('(');
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

FungeStrategy* Unefunge98Strategy::clone(FungeRunner& r) const{
	return new Unefunge98Strategy(r);
}

}
