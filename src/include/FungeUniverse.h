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
#include "FungeSem.h"
#include <condition_variable>
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
		FungeUniverse(std::istream& file, Field::FileFormat fmt, const FungeConfig& cfg);
		
		/**
		 * Copy constructor.
		 */
		FungeUniverse(const FungeUniverse& old) = delete;

		FungeUniverse& operator=(const FungeUniverse& other) = delete;

		/**
		 * Destructor.
		 */
		virtual ~FungeUniverse();

		/**
		 * Wait for the universe to end.
		 */
		void wait() const;

		/**
		 * Get the exit code from the universe.
		 * @return Exit code.
		 */
		int get() const;

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

		/**
		 * Create a new runner.
		 * @param pos Initial position.
		 * @param delta Initial delta.
		 * @param r Runner creating the new runner.
		 */
		void createRunner(const Vector& pos, const Vector& delta, FungeRunner& r);

		/**
		 * Transfer a runner from another universe
		 * @param runner Runner to transfer.
		 */
		void transferRunner(FungeRunner* runner);

		/**
		 * Determine how the universe was created.
		 * @return runner that created the universe.
		 */
		FungeRunner* getCreator() const;

		void operator()();

		FungeDebugger& getDebugger();
		const std::string& getName() const;
		const std::vector<std::string>& arguments() const;
		const std::vector<std::string>& environment() const;
		const std::vector<uint64_t>& fingerprints() const;
		FungeRunner* getRunner(size_t id);
		size_t dimensions(size_t d=0);
		unsigned int standard() const;
		FungeTopo topology() const;
		FungeString stringStyle() const;
		FungeCell cellSize() const;
		void setMode(FungeMode m);
		void clearMode(FungeMode m);
		void toggleMode(FungeMode m);
		stack_t getMode() const;
		bool isMode(FungeMode m) const;
		bool allowConcurrent() const;
		bool allowExecute() const;
		bool allowFilesystem() const;
		bool allowFingerprints() const;
		bool invertHL() const;
	
	private:
		bool running;
		int exitcode;
		FungeConfig config;
		FungeDebugger debug;
		Field field;
		std::thread* thread;
		std::queue<std::thread*> threads;
		std::list<FungeRunner*> runners;
		FungeRunner* creator;
		FungeSem semaphore;
		mutable std::mutex mutex;
		mutable std::condition_variable cv;
		
		explicit FungeUniverse(const FungeConfig& cfg);
		void addRunner(FungeRunner* runner);

		friend class FungeMultiverse;
};

}
