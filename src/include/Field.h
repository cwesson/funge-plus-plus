/**
 * @file Field.h
 * Represents the instructions in Funge-space.
 * @author Conlan Wesson
 */

#pragma once

#include <iostream>
#include <map>
#include "Vector.h"
#include "funge_types.h"

namespace Funge {

class Field {
	public:
		enum FileFormat {
			FORMAT_BF,
			FORMAT_BEQ,
		};
		
		Field();
		explicit Field(std::istream& file, size_t dim, FileFormat fmt);
		
		void set(const Vector& p, inst_t v);
		inst_t get(const Vector& p) const;
		
		Vector parse(const Vector& start, std::istream& file, bool binary=false);
		void dump(const Vector& start, const Vector& delta, std::ostream& file, bool binary=false);
		void parseBeq(std::istream& file);
		
		dim_t min(size_t d) const;
		dim_t max(size_t d) const;
		
		inst_t operator[](const Vector& v) const;
		
		friend std::ostream& operator<<(std::ostream& os, const Field& rhs);
	
	private:
		std::map<const Vector, inst_t> field;
		std::vector<dim_t> maxs;
		std::vector<dim_t> mins;
		
		void increment(dim_t d, Vector& v, Vector& max);
		void reset(dim_t d, Vector& v, const Vector& start, Vector& max);
};

}
