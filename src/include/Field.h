/**
 * @file Field.h
 * Represents the instructions in fungespace.
 * @author Conlan Wesson
 */

#pragma once

#include "Vector.h"
#include "funge_types.h"
#include <iostream>
#include <map>

namespace Funge {
class FungeUniverse;

/**
 * Stores the state of the fungespace.
 */
class Field {
	public:
		/**
		 * Input file formats.
		 */
		enum FileFormat {
			FORMAT_BF,  ///< Befunge formatted files.
			FORMAT_BEQ, ///< BeQunge formatted files.
			FORMAT_FL,  ///< Funge-lib formatted files.
		};
		
		Field() = delete;

		/**
		 * Constructor.
		 * @param file Input file stream.
		 * @param fmt Input file format.
		 * @param dim Initial number of dimensions.
		 * @param uni Universe the Field is part of.
		 */
		Field(std::istream& file, FileFormat fmt, size_t dim, FungeUniverse& uni);

		/**
		 * Constructor.
		 * @param dim Initial number of dimensions.
		 * @param uni Universe the Field is part of.
		 */
		Field(size_t dim, FungeUniverse& uni);
		
		/**
		 * Set the value at position p.
		 * @param p Position to set.
		 * @param v New value.
		 */
		void set(const Vector& p, inst_t v);

		/**
		 * Get the value at position p.
		 * @param p Position to get.
		 * @return Value at position p.
		 */
		inst_t get(const Vector& p) const;
		
		/**
		 * Parse a Befunge formatted file.
		 * @param start Starting position of file.
		 * @param file Input file stream.
		 * @param binary true if file is non-text.
		 * @return Size of space parsed.
		 */
		Vector parse(const Vector& start, std::istream& file, bool binary=false);

		/**
		 * Dump the fungespace to a file.
		 * @param start Starting position.
		 * @param delta Size of space to dump.
		 * @param file Output file stream.
		 * @param binary true to dump as non-text.
		 */
		void dump(const Vector& start, const Vector& delta, std::ostream& file, bool binary=false) const;

		/**
		 * Get the fungespace topology.
		 * @return Fungespace topology.
		 */
		FungeTopo topology() const;

		/**
		 * Get the number of dimensions of the fungespace.
		 * @return Number of dimensions.
		 */
		size_t dimensions() const;

		/**
		 * Get the minimum position in dimension d.
		 * @param d Dimension to check.
		 * @return Minimum position.
		 */
		dim_t min(size_t d) const;

		/**
		 * Get the Maximum position in dimension d.
		 * @param d Dimension to check.
		 * @return Maximum position.
		 */
		dim_t max(size_t d) const;

		/**
		 * Get the universe the fungespace is in.
		 * @return Universe.
		 */
		FungeUniverse& getUniverse();
		
		/**
		 * Get the value at position v.
		 * @param v Position to get.
		 * @return Value at position v.
		 */
		inst_t operator[](const Vector& v) const;

		/**
		 * Determine which planes the loaded FungeLib has.
		 * @return List of planes.
		 */
		const std::vector<inst_t>& hasPlanes() const;
		
		/**
		 * Output stream operator.
		 */
		friend std::ostream& operator<<(std::ostream& os, const Field& rhs);
	
	private:
		FungeUniverse& universe;
		std::map<const Vector, inst_t> field;
		std::vector<dim_t> maxs;
		std::vector<dim_t> mins;
		std::vector<inst_t> planes;
		
		void parseBeq(std::istream& file);
		void parseFungeLib(std::istream& file);
		void increment(dim_t d, Vector& v, Vector& max);
		void reset(dim_t d, Vector& v, const Vector& start, Vector& max);
};

}
