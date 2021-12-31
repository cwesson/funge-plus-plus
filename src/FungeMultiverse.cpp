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
		uni.second->waitAll();
		// Destroy the universe
		delete uni.second;
	}
}

FungeMultiverse& FungeMultiverse::getInstance(){
	static FungeMultiverse instance;
	return instance;
}

FungeUniverse* FungeMultiverse::create(std::istream& file, Field::FileFormat fmt, const FungeConfig* cfg){
	if(!universes.contains(cfg->name)){
		FungeUniverse* uni = new FungeUniverse(file, fmt, cfg);
		universes[cfg->name] = uni;
		return uni;
	}
	return nullptr;
}

int FungeMultiverse::waitAll(){
	bool first = true;
	bool running = false;
	int ret = 0;
	do{
		running = false;
		for(auto next : universes){
			FungeUniverse* uni = next.second;
			if(uni->isRunning()){
				running = true;
				int r = uni->waitAll();
				// Only keep exit code from the prime universe
				if(first){
					ret = r;
					first = false;
				}
			}
		}
		// Keep looping until all universes are dead
	}while(running);

	return ret;
}

FungeUniverse* FungeMultiverse::operator[](std::string name){
	if(universes.contains(name)){
		return universes[name];
	}
	return nullptr;
}

size_t FungeMultiverse::size(){
	return universes.size();
}

}
