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
