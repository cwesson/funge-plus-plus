/**
 * @file Vector.h
 * Represents an N-dimensional vector.
 * @author Conlan Wesson
 */

#pragma once

#include <iostream>
#include <vector>
#include "funge_types.h"

namespace Funge {
	
class Vector {
	public:
		Vector();
		explicit Vector(std::initializer_list<dim_t> v);
		Vector(const Vector& orig);
		Vector& operator=(const Vector& orig);
		Vector& operator=(std::initializer_list<dim_t> orig);
		
		size_t size() const;
		
		dim_t get(size_t d) const;
		void set(size_t d, dim_t v);
		
		void reverse();
		void left();
		void right();
		
		dim_t operator[](size_t x) const;
		
		Vector& operator+=(const Vector& other);
		friend Vector operator+(const Vector& lhs, const Vector& rhs);
		Vector& operator-=(const Vector& other);
		friend Vector operator-(const Vector& lhs, const Vector& rhs);
		
		bool operator<(const Vector& other) const;
		bool operator<=(const Vector& other) const;
		bool operator==(const Vector& other) const;
		bool operator!=(const Vector& other) const;
		
		friend std::ostream& operator<<(std::ostream& os, const Vector& rhs);
		friend std::istream& operator>>(std::istream& is, Vector& rhs);
	
	private:
		std::vector<dim_t> values;
		void normalize();
};

}
