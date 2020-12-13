/**
 * @file FungeUniverse.cpp
 * Funge Universe.
 * @author Conlan Wesson
 */

#include "FungeUniverse.h"
#include "FungeRunner.h"
#include "FungeConfig.h"

namespace Funge {

FungeUniverse::FungeUniverse(std::istream& file, size_t dim, Field::FileFormat fmt):
	field(file, dim, fmt),
	runners(),
	mutex()
{
	addRunner(new FungeRunner(*this));
}

FungeUniverse::FungeUniverse(const FungeUniverse& old):
	field(old.field),
	runners(),
	mutex()
{
}

FungeUniverse::~FungeUniverse(){
	std::lock_guard<std::mutex> guard(mutex);
	while(threads.size() > 0){
		std::thread* thread = threads.front();
		thread->join();
		delete thread;
	}
	while(runners.size() > 0){
		FungeRunner* runner = runners.front();
		delete runner;
	}
}

void FungeUniverse::cloneRunner(FungeRunner& runner){
	addRunner(new FungeRunner(*this, runner));
}

void FungeUniverse::addRunner(FungeRunner* runner){
	std::lock_guard<std::mutex> guard(mutex);
	if(funge_config.threads == THREAD_NATIVE){
		std::thread* thread = new std::thread(std::ref(*runner));
		threads.push(thread);
	}
	runners.push(runner);
}

void FungeUniverse::waitAll(){
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
			thread->tick();
			if(thread->isRunning()){
				mutex.lock();
				runners.push(thread);
				mutex.unlock();
			}else{
				delete thread;
			}
		}
	}
}

Field& FungeUniverse::getField(){
	return field;
}

}
