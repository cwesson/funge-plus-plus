/**
 * @file FungeUniverse.cpp
 * Funge Universe.
 * @author Conlan Wesson
 */

#include "FungeUniverse.h"
#include "FungeRunner.h"
#include "FungeConfig.h"

namespace Funge {

FungeUniverse::FungeUniverse(std::istream& file, Field::FileFormat fmt, const struct FungeConfig* cfg):
	exitcode(0),
	config(*cfg),
	debug(),
	field(file, fmt, cfg->dimensions, *this),
	runners(),
	mutex()
{
	addRunner(new FungeRunner(*this));
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
		runners.pop_front();
	}
}

void FungeUniverse::cloneRunner(FungeRunner& runner){
	addRunner(new FungeRunner(runner));
}

void FungeUniverse::addRunner(FungeRunner* runner){
	std::lock_guard<std::mutex> guard(mutex);
	if(config.threads == THREAD_NATIVE){
		std::thread* thread = new std::thread(std::ref(*runner));
		threads.push(thread);
	}
	runners.push_back(runner);
}

int FungeUniverse::waitAll(){
	if(config.threads == THREAD_NATIVE){
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
			mutex.unlock();
			if(thread->isRunning()){
				thread->tick();
			}
			runners.pop_front();
			if(thread->isRunning()){
				mutex.lock();
				runners.push_back(thread);
				mutex.unlock();
			}else{
				delete thread;
			}
		}
	}
	return exitcode;
}

void FungeUniverse::killAll(int ret){
	std::lock_guard<std::mutex> guard(mutex);
	exitcode = ret;
	for(auto runner : runners){
		runner->getIP().stop();
	}
}

Field& FungeUniverse::getField(){
	return field;
}

FungeDebugger& FungeUniverse::getDebugger(){
	return debug;
}

const std::string& FungeUniverse::getName(){
	return config.name;
}

const std::vector<std::string>& FungeUniverse::arguments(){
	return config.args;
}

const std::vector<std::string>& FungeUniverse::environment(){
	return config.env;
}

const std::vector<uint64_t>& FungeUniverse::fingerprints(){
	return config.fingerprints;
}

size_t FungeUniverse::dimensions(size_t d){
	if(d > 0){
		config.dimensions = d;
	}
	return config.dimensions;
}

unsigned int FungeUniverse::standard(){
	return config.standard;
}

FungeTopo FungeUniverse::topology(){
	return config.topo;
}

FungeString FungeUniverse::stringStyle(){
	return config.strings;
}

FungeCell FungeUniverse::cellSize(){
	return config.cells;
}

void FungeUniverse::setMode(FungeMode m){
	config.mode |= m;
}

void FungeUniverse::clearMode(FungeMode m){
	config.mode &= ~m;
}

void FungeUniverse::toggleMode(FungeMode m){
	config.mode ^= m;
}

bool FungeUniverse::isMode(FungeMode m){
	return !!(config.mode & m);
}

bool FungeUniverse::allowConcurrent(){
	return config.concurrent;
}

bool FungeUniverse::allowExecute(){
	return config.execute;
}

bool FungeUniverse::allowFilesystem(){
	return config.filesystem;
}

bool FungeUniverse::allowFingerprints(){
	return config.fingerprint;
}

bool FungeUniverse::invertHL(){
	return config.inverthl;
}

}
