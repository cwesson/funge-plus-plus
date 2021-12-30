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

/**
 * Stores an N-dimensional vector.
 */
class Vector {
	public:
		/**
		 * Constructor.
		 */
		Vector();

		/**
		 * Initializer list constructor.
		 * @param v Initializer list.
		 */
		explicit Vector(std::initializer_list<dim_t> v);

		/**
		 * Copy constructor.
		 * @param orig Original Vector.
		 */
		Vector(const Vector& orig);

		/**
		 * Assignment operator.
		 * @param orig Original Vector.
		 * @return New Vector.
		 */
		Vector& operator=(const Vector& orig);

		/**
		 * Assignment operator.
		 * @param orig Initializer list.
		 * @return New Vector.
		 */
		Vector& operator=(std::initializer_list<dim_t> orig);

		/**
		 * Get the number of dimensions.
		 * @return Number of dimensions.
		 */
		size_t size() const;

		/**
		 * Get the magnitude in dimension d.
		 * @param d Dimension to get.
		 * @return Magnitude in dimension d.
		 */
		dim_t get(size_t d) const;

		/**
		 * Set the magnitude in dimension d.
		 * @param d Dimension to set.
		 * @param v Magnitude in dimension d.
		 */
		void set(size_t d, dim_t v);

		/**
		 * Reverse the direction.
		 */
		void reverse();

		/**
		 * Turn left about the Z axis.
		 */
		void left();

		/**
		 * Turn left about the Z axis.
		 */
		void right();

		/**
		 * Get the magnitude in dimension x.
		 * @param x Dimension to get.
		 * @return Magnitude in dimension x.
		 */
		dim_t operator[](size_t x) const;

		/**
		 * Add two vectors.
		 */
		Vector& operator+=(const Vector& other);
		friend Vector operator+(const Vector& lhs, const Vector& rhs);

		/**
		 * Subtract two vectors.
		 */
		Vector& operator-=(const Vector& other);
		friend Vector operator-(const Vector& lhs, const Vector& rhs);
		
		/**
		 * Compare two vectors.
		 */
		bool operator<(const Vector& other) const;
		bool operator<=(const Vector& other) const;
		bool operator==(const Vector& other) const;
		bool operator!=(const Vector& other) const;
		
		/**
		 * Output stream operator.
		 */
		friend std::ostream& operator<<(std::ostream& os, const Vector& rhs);

		/**
		 * Input stream operator.
		 */
		friend std::istream& operator>>(std::istream& is, Vector& rhs);
	
	private:
		std::vector<dim_t> values;
		void normalize();
};

}
