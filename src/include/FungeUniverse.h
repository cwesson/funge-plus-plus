/**
 * @file FungeUniverse.h
 * Funge Universe.
 * @author Conlan Wesson
 */

#pragma once

#include "Field.h"
#include "FungeConfig.h"
#include "FungeDebugger.h"
#include <mutex>
#include <iostream>
#include <thread>
#include <queue>

namespace Funge {
class FungeRunner;

class FungeUniverse {
	public:
		FungeUniverse(std::istream& file, Field::FileFormat fmt, const struct FungeConfig* cfg);
		FungeUniverse(const FungeUniverse& old) = delete;
		virtual ~FungeUniverse();
		
		void waitAll();
		
		Field& getField();
		
		void cloneRunner(FungeRunner& runner);

		FungeDebugger& getDebugger();
		const std::string& getName();
		const std::vector<std::string>& arguments();
		const std::vector<std::string>& environment();
		const std::vector<uint64_t>& fingerprints();
		size_t dimensions(size_t d=0);
		unsigned int standard();
		FungeTopo topology();
		FungeString stringStyle();
		FungeCell cellSize();
		void setMode(FungeMode m);
		void clearMode(FungeMode m);
		void toggleMode(FungeMode m);
		bool isMode(FungeMode m);
		bool allowConcurrent();
		bool allowExecute();
		bool allowFilesystem();
		bool allowFingerprints();
		bool invertHL();
	
	private:
		struct FungeConfig config;
		FungeDebugger debug;
		Field field;
		std::queue<std::thread*> threads;
		std::queue<FungeRunner*> runners;
		std::mutex mutex;
		
		void addRunner(FungeRunner* runner);
};

}
