/**
 * @file FungeManager.cpp
 * Manages FungeRunners.
 * @author Conlan Wesson
 */

#include "FungeManager.h"
#include "FungeConfig.h"

namespace Funge {

FungeManager* FungeManager::instance = new FungeManager();

FungeManager::FungeManager() :
	threads(),
	runners(),
	mutex()
{

}

FungeManager* FungeManager::getInstance() {
	return instance;
}

void FungeManager::addRunner(FungeRunner* runner){
	std::lock_guard<std::mutex> guard(mutex);
	if(funge_config.threads == THREAD_NATIVE){
		std::thread* thread = new std::thread(std::ref(*runner));
		threads.push(thread);
	}
	runners.push(runner);
}

void FungeManager::waitAll(){
	if(funge_config.threads == THREAD_NATIVE){
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
	}else{
		while(runners.size() > 0){
			mutex.lock();
			FungeRunner* thread = runners.front();
			runners.pop();
			mutex.unlock();
			//std::cout << "tick" << std::endl;
			thread->tick();
			if(thread->isRunning()){
				mutex.lock();
				runners.push(thread);
				mutex.unlock();
			}
		}
	}
}

}
