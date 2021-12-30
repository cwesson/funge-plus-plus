/**
 * @file FungeUniverse.h
 * Funge Universe.
 * @author Conlan Wesson
 */

#pragma once

#include "Field.h"
#include "FungeConfig.h"
#include "FungeRunner.h"
#include "FungeDebugger.h"
#include <mutex>
#include <iostream>
#include <thread>
#include <queue>

namespace Funge {
class FungeRunner;

class FungeUniverse {
	public:
		FungeUniverse(const FungeUniverse& old) = delete;
		virtual ~FungeUniverse();
		
		int waitAll();
		void killAll(int ret);
		
		Field& getField();
		
		void cloneRunner(FungeRunner& runner);
		void createRunner(const Vector& pos, const Vector& delta);

		FungeDebugger& getDebugger();
		const std::string& getName() const;
		const std::vector<std::string>& arguments() const;
		const std::vector<std::string>& environment() const;
		const std::vector<uint64_t>& fingerprints() const;
		size_t dimensions(size_t d=0);
		unsigned int standard() const;
		FungeTopo topology() const;
		FungeString stringStyle() const;
		FungeCell cellSize() const;
		void setMode(FungeMode m);
		void clearMode(FungeMode m);
		void toggleMode(FungeMode m);
		bool isMode(FungeMode m) const;
		bool allowConcurrent() const;
		bool allowExecute() const;
		bool allowFilesystem() const;
		bool allowFingerprints() const;
		bool invertHL() const;
	
	private:
		int exitcode;
		FungeConfig config;
		FungeDebugger debug;
		Field field;
		std::queue<std::thread*> threads;
		std::list<FungeRunner*> runners;
		std::mutex mutex;
		
		FungeUniverse(std::istream& file, Field::FileFormat fmt, const FungeConfig* cfg);
		void addRunner(FungeRunner* runner);

		friend class FungeMultiverse;
};

}
