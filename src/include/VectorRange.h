/**
 * @file VectorRange.h
 * Range iterator for Vectors.
 * @author Conlan Wesson
 */

#pragma once

#include <iostream>
#include "Vector.h"
#include "funge_types.h"

namespace Funge {
	
class VectorRange {
	public:
		VectorRange(const Vector& vfirst, const Vector& vlast);
		
		const Vector& begin();
		const Vector& end();
		
		Vector& operator*();
		VectorRange& operator++();
		VectorRange operator++(int);
	
	private:
		const Vector vbegin;
		const Vector vlast;
		Vector vend;
		Vector current;
};

}
