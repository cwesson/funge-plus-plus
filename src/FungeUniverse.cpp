/**
 * @file FungeUniverse.cpp
 * Funge Universe.
 * @author Conlan Wesson
 */

#include "FungeUniverse.h"
#include "FungeRunner.h"
#include "FungeConfig.h"

namespace Funge {

FungeUniverse::FungeUniverse(std::istream& file, Field::FileFormat fmt, const FungeConfig& cfg):
	running(true),
	exitcode(0),
	config(cfg),
	debug(*this),
	field(file, fmt, cfg.dimensions, *this),
	thread(nullptr),
	threads(),
	runners(),
	creator(nullptr),
	semaphore(0),
	mutex(),
	cv()
{
	thread = new std::thread(std::ref(*this));
}

FungeUniverse::FungeUniverse(const FungeConfig& cfg):
	running(true),
	exitcode(0),
	config(cfg),
	debug(*this),
	field(cfg.dimensions, *this),
	thread(nullptr),
	threads(),
	runners(),
	creator(nullptr),
	semaphore(0),
	mutex(),
	cv()
{
	thread = new std::thread(std::ref(*this));
}

FungeUniverse::~FungeUniverse(){
	killAll(1);
	thread->join();

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

	delete thread;
}

void FungeUniverse::cloneRunner(FungeRunner& runner){
	addRunner(new FungeRunner(runner));
}

void FungeUniverse::createRunner(const Vector& pos, const Vector& delta){
	addRunner(new FungeRunner(*this, pos, delta));
}

void FungeUniverse::createRunner(const Vector& pos, const Vector& delta, FungeRunner& r){
	FungeRunner* runner = new FungeRunner(*this, pos, delta, r);
	addRunner(runner);
}

void FungeUniverse::transferRunner(FungeRunner* runner){
	if(&runner->getUniverse() != this){
		std::lock_guard<std::mutex> guard(mutex);
		runner->setUniverse(*this);
		runners.push_back(runner);
		semaphore.release();
	}
}

void FungeUniverse::addRunner(FungeRunner* runner){
	std::lock_guard<std::mutex> guard(mutex);
	if(config.threads == THREAD_NATIVE){
		std::thread* thread = new std::thread(std::ref(*runner));
		threads.push(thread);
	}
	runners.push_back(runner);
	semaphore.release();
}

void FungeUniverse::operator()(){
	while(running){
		semaphore.acquire();
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
			mutex.lock();
			while(runners.size() > 0){
				FungeRunner* thread = runners.front();

				mutex.unlock();
				if(thread->isRunning()){
					thread->tick();
				}
				mutex.lock();

				runners.pop_front();
				if(&thread->getUniverse() == this){
					if(thread->isRunning()){
						runners.push_back(thread);
					}else{
						debug.endThread(*thread);
						delete thread;
						cv.notify_all();
					}
				}else{
					cv.notify_all();
				}
			}
			mutex.unlock();
		}
	}
}

void FungeUniverse::wait() const{
	std::unique_lock<std::mutex> lock(mutex);
	cv.wait(lock, [this]{return !isRunning();});
}

int FungeUniverse::get() const{
	return exitcode;
}

void FungeUniverse::killAll(int ret){
	std::lock_guard<std::mutex> guard(mutex);
	exitcode = ret;
	for(auto runner : runners){
		runner->getIP().stop();
	}
	running = false;
	semaphore.release();
	cv.notify_all();
}

bool FungeUniverse::isRunning() const{
	bool alive = (runners.size() > 0);
	if(config.threads == THREAD_NATIVE){
		alive = (threads.size() > 0);
	}
	return running && alive;
}

Field& FungeUniverse::getField(){
	return field;
}

FungeDebugger& FungeUniverse::getDebugger(){
	return debug;
}

FungeRunner* FungeUniverse::getCreator() const{
	return creator;
}

const std::string& FungeUniverse::getName() const {
	return config.name;
}

const std::vector<std::string>& FungeUniverse::arguments() const {
	return config.args;
}

const std::vector<std::string>& FungeUniverse::environment() const {
	return config.env;
}

const std::vector<uint64_t>& FungeUniverse::fingerprints() const {
	return config.fingerprints;
}

FungeRunner* FungeUniverse::getRunner(size_t id){
	for(auto r : runners){
		if(r->getID() == id){
			return r;
		}
	}
	return nullptr;
}

size_t FungeUniverse::dimensions(size_t d){
	if(d > 0){
		config.dimensions = d;
	}
	return config.dimensions;
}

FungeStandard FungeUniverse::standard() const {
	return config.standard;
}

FungeTopo FungeUniverse::topology() const {
	return config.topo;
}

FungeString FungeUniverse::stringStyle() const {
	return config.strings;
}

FungeCell FungeUniverse::cellSize() const {
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

stack_t FungeUniverse::getMode() const {
	return config.mode;
}

bool FungeUniverse::isMode(FungeMode m) const {
	return !!(config.mode & m);
}

bool FungeUniverse::allowConcurrent() const {
	return config.concurrent;
}

bool FungeUniverse::allowExecute() const {
	return config.execute;
}

bool FungeUniverse::allowFilesystem() const {
	return config.filesystem;
}

bool FungeUniverse::allowFingerprints() const {
	return config.fingerprint;
}

bool FungeUniverse::invertHL() const {
	return config.inverthl;
}

}
