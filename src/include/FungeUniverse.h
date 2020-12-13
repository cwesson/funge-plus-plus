/**
 * @file FungeUniverse.h
 * Funge Universe.
 * @author Conlan Wesson
 */

#pragma once

#include "Field.h"
#include <mutex>
#include <iostream>
#include <thread>
#include <queue>

namespace Funge {
class FungeRunner;

class FungeUniverse {
	public:
		FungeUniverse(std::istream& file, size_t dim, Field::FileFormat fmt);
		FungeUniverse(const FungeUniverse& old);
		virtual ~FungeUniverse();
		
		void waitAll();
		
		Field& getField();
		
		void cloneRunner(FungeRunner& runner);
	
	private:
		Field field;
		std::queue<std::thread*> threads;
		std::queue<FungeRunner*> runners;
		std::mutex mutex;
		
		void addRunner(FungeRunner* runner);
};

}
