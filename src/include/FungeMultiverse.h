/**
 * @file FungeMultiverse.h
 * Manages funge universes.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeUniverse.h"
#include <map>
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

		/**
		 * Create a new universe.
		 * @param file Fungespace input file.
		 * @param fmt Format of the input file.
		 * @param cfg Configuration for the universe.
		 * @return New universe.
		 */
		FungeUniverse* create(std::istream& file, Field::FileFormat fmt, FungeConfig* cfg);

		/**
		 * Wait for all universes to end.
		 * @return Exist code from the prime universe.
		 */
		int waitAll();

		/**
		 * Lookup universe by name.
		 * @param name Name to lookup.
		 * @return The universe found or nullptr.
		 */
		FungeUniverse* operator[](std::string name);

		std::map<std::string, FungeUniverse*>::const_iterator cbegin() const;
		std::map<std::string, FungeUniverse*>::const_iterator cend() const;

		/**
		 * Get the size of the multiverse.
		 * @return Number of universes in the multiverse.
		 */
		size_t size() const;
	
	private:
		std::map<std::string, FungeUniverse*> universes;
		mutable std::mutex mutex;

		FungeMultiverse();
		~FungeMultiverse();
};

}
