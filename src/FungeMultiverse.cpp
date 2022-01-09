/**
 * @file FungeMultiverse.cpp
 * Manages funge universes.
 * @author Conlan Wesson
 */

#include "FungeMultiverse.h"

namespace Funge {

FungeMultiverse::FungeMultiverse() :
	universes()
{

}

FungeMultiverse::~FungeMultiverse(){
	for(auto uni : universes){
		// Destroy the universe
		delete uni.second;
	}
}

FungeMultiverse& FungeMultiverse::getInstance(){
	static FungeMultiverse instance;
	return instance;
}

FungeUniverse* FungeMultiverse::create(std::istream& file, Field::FileFormat fmt, FungeConfig* cfg){
	unsigned int a = 1;
	std::string name(cfg->name);
	while(universes.contains(cfg->name)){
		cfg->name = name + "." + std::to_string(a);
	}
	FungeUniverse* uni = new FungeUniverse(file, fmt, cfg);
	universes[cfg->name] = uni;
	return uni;
}

FungeUniverse* FungeMultiverse::create(FungeConfig* cfg){
	unsigned int a = 1;
	std::string name(cfg->name);
	while(universes.contains(cfg->name)){
		cfg->name = name + "." + std::to_string(a);
	}
	FungeUniverse* uni = new FungeUniverse(cfg);
	universes[cfg->name] = uni;
	return uni;
}

int FungeMultiverse::waitAll(){
	bool running = false;
	size_t count = 0;
	do{
		running = false;
		for(auto next : universes){
			const FungeUniverse* uni = next.second;
			if(uni->isRunning()){
				running = true;
			}
			uni->wait();
			++count;
		}
		// Keep looping until all universes are dead
	}while(running || count < universes.size());

	int ret = 0;
	for(auto next : universes){
		ret = next.second->get();
		break;
	}

	return ret;
}

void FungeMultiverse::killAll(int ret){
	for(auto next : universes){
		next.second->killAll(ret);
	}
}

FungeUniverse* FungeMultiverse::operator[](std::string name){
	if(universes.contains(name)){
		return universes[name];
	}
	return nullptr;
}

std::map<std::string, FungeUniverse*>::const_iterator FungeMultiverse::cbegin() const{
	return universes.cbegin();
}
std::map<std::string, FungeUniverse*>::const_iterator FungeMultiverse::cend() const{
	return universes.cend();
}

size_t FungeMultiverse::size() const{
	return universes.size();
}

}
