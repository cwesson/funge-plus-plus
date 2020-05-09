/**
 * @file FungeManager.h
 * Manages FungeRunners.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeRunner.h"
#include <mutex>
#include <thread>
#include <queue>

namespace Funge {

class FungeManager {
	public:
		static FungeManager* getInstance();
		void waitAll();
	
	private:
		FungeManager();
		~FungeManager();
		void addRunner(FungeRunner* runner);
		
		static FungeManager* instance;
		std::queue<std::thread*> threads;
		std::queue<FungeRunner*> runners;
		std::mutex mutex;
		
	friend class FungeRunner;
};

}
