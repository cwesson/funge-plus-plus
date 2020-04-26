/**
 * @file FungeManager.cpp
 * Manages FungeRunners.
 * @author Conlan Wesson
 */

#include "FungeManager.h"

namespace Funge {

FungeManager* FungeManager::instance = new FungeManager();

FungeManager::FungeManager() : threads(), mutex() {

}

FungeManager* FungeManager::getInstance() {
	return instance;
}

void FungeManager::addRunner(FungeRunner& runner){
	std::lock_guard<std::mutex> guard(mutex);
	std::thread* thread = new std::thread(std::ref(runner));
	threads.push(thread);
}

void FungeManager::waitAll(){
	mutex.lock();
	while(threads.size() > 0){
		std::thread* thread = threads.front();
		if(thread->joinable()){
			mutex.unlock();
			thread->join();
			mutex.lock();
		}
		threads.pop();
		delete thread;
	}
	mutex.unlock();
}

}
