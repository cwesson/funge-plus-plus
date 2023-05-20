/**
 * @file FungeMultiverse.h
 * Manages funge universes.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeUniverse.h"
#include <unordered_map>
#include <mutex>

namespace Funge {

/**
 * Funge multiverse.
 */
class FungeMultiverse {
	public:
		/**
		 * Get the multiverse instance.
		 * @return The multiverse.
		 */
		static FungeMultiverse& getInstance();

		FungeMultiverse(const FungeMultiverse& orig) = delete;
		FungeMultiverse operator=(const FungeMultiverse& orig) = delete;

		/**
		 * Create a new universe.
		 * @param file Fungespace input file.
		 * @param fmt Format of the input file.
		 * @param cfg Configuration for the universe.
		 * @param creator Creating runner.
		 * @return New universe.
		 */
		FungeUniverse* create(std::istream& file, Field::FileFormat fmt, FungeConfig& cfg, FungeRunner* creator=nullptr);

		/**
		 * Create a new universe.
		 * @param cfg Configuration for the universe.
		 * @return New universe.
		 */
		FungeUniverse* create(FungeConfig& cfg);

		/**
		 * Wait for all universes to end.
		 * @return Exist code from the prime universe.
		 */
		int waitAll();

		/**
		 * Kill all universes.
		 * @param ret Exit code to use.
		 */
		void killAll(int ret);

		/**
		 * Lookup universe by name.
		 * @param name Name to lookup.
		 * @return The universe found or nullptr.
		 */
		FungeUniverse* operator[](std::string name);

		std::unordered_map<std::string, FungeUniverse*>::const_iterator cbegin() const;
		std::unordered_map<std::string, FungeUniverse*>::const_iterator cend() const;

		/**
		 * Get the size of the multiverse.
		 * @return Number of universes in the multiverse.
		 */
		size_t size() const;
	
	private:
		FungeUniverse* prime;
		std::unordered_map<std::string, FungeUniverse*> universes;
		mutable std::mutex mutex;

		FungeMultiverse();
		~FungeMultiverse();
};

}
