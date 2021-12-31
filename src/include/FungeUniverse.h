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

/**
 * Funge universe.
 */
class FungeUniverse {
	public:
		/**
		 * Copy constructor.
		 */
		FungeUniverse(const FungeUniverse& old) = delete;

		/**
		 * Destructor.
		 */
		virtual ~FungeUniverse();

		/**
		 * Wait for the universe to end.
		 * @return Exit code from the universe.
		 */
		int waitAll();

		/**
		 * Kill all runners in the universe.
		 * @param ret Exit code to use.
		 */
		void killAll(int ret);

		/**
		 * Check if the universe is running.
		 * @return true if there are runners in the universe.
		 */
		bool isRunning() const;

		/**
		 * Get the field of the universe.
		 * @return The field.
		 */
		Field& getField();

		/**
		 * Clone an existing runner.
		 * @param runner Runner to clone.
		 */
		void cloneRunner(FungeRunner& runner);

		/**
		 * Create a new runner.
		 * @param pos Initial position.
		 * @param delta Initial delta.
		 */
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
		mutable std::mutex mutex;
		
		FungeUniverse(std::istream& file, Field::FileFormat fmt, const FungeConfig* cfg);
		void addRunner(FungeRunner* runner);

		friend class FungeMultiverse;
};

}
