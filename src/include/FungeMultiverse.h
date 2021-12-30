/**
 * @file FungeMultiverse.h
 * Manages funge universes.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeUniverse.h"

namespace Funge {

class FungeMultiverse {
	public:
		static FungeMultiverse& getInstance();

		FungeUniverse* create(std::istream& file, Field::FileFormat fmt, const FungeConfig* cfg);

		FungeUniverse* operator[](std::string name);
		size_t size();
	
	private:
		std::map<std::string, FungeUniverse*> universes;

		FungeMultiverse();
		~FungeMultiverse();
};

}
