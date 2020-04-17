/**
 * @file Field.h
 * Represents the instructions in Funge-space.
 * @author Conlan Wesson
 */

#pragma once

#include <iostream>
#include <map>
#include "Vector.h"
#include "funge_common.h"

namespace Funge {

class Field {
	public:
		explicit Field(std::istream& file);
		
		void set(const Vector& p, inst_t v);
		inst_t get(const Vector& p) const;
		
		size_t dimensions() const;
		dim_t min(size_t d) const;
		dim_t max(size_t d) const;
		
		inst_t operator[](const Vector& v) const;
		
		friend std::ostream& operator<<(std::ostream& os, const Field& rhs);
	
	private:
		std::map<Vector, inst_t> field;
		std::vector<dim_t> maxs;
		std::vector<dim_t> mins;
};

}
