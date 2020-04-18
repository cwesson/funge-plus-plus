/**
 * @file Vector.cpp
 * Represents an N-dimensional vector.
 * @author Conlan Wesson
 */

#include "Vector.h"
#include <cmath>

namespace Funge {

Vector::Vector(){
	
}

Vector::Vector(const Vector& orig) : values(orig.values){

}

Vector::Vector(std::initializer_list<dim_t> v){
	for(dim_t d : v){
		values.push_back(d);
	}
}

Vector& Vector::operator=(const Vector& orig){
	values.clear();
	for(dim_t d : orig.values){
		values.push_back(d);
	}
	return *this;
}

size_t Vector::size() const{
	return values.size();
}

dim_t Vector::get(size_t d) const{
	dim_t ret = 0;
	if(d < values.size()){
		ret = values[d];
	}
	return ret;
}

void Vector::set(size_t d, dim_t v){
	while(d >= values.size()){
		values.push_back(0);
	}
	values[d] = v;
}

void Vector::reverse(){
	for(size_t i = 0; i < values.size(); ++i){
		set(i, -get(i));
	}
}

void Vector::left(){
	dim_t tx = get(0);
	dim_t ty = get(1);
	set(0, ty);
	set(1, -tx);
}

void Vector::right(){
	dim_t tx = get(0);
	dim_t ty = get(1);
	set(0, -ty);
	set(1, tx);
}

dim_t Vector::operator[](size_t x) const{
	return this->get(x);
}

dim_t& Vector::operator[](size_t x){
	return values[x];
}

Vector& Vector::operator+=(const Vector& other){
	size_t len = std::max(this->values.size(), other.values.size());
	for(size_t i = 0; i < len; ++i){
		this->set(i, this->get(i)+other.get(i));
	}
	return *this;
}

Vector operator+(const Vector& lhs, const Vector& rhs) {
	return Vector(lhs) += rhs;
}

bool Vector::operator<(const Vector& other) const{
	size_t len = std::max(this->values.size(), other.values.size());
	for(size_t i = len; i > 0; --i){
		dim_t lhs = this->get(i-1);
		dim_t rhs = other.get(i-1);
		if(lhs > rhs){
			return false;
		}else if(lhs < rhs){
			return true;
		}
	}
	return false;
}

bool Vector::operator==(const Vector& other) const{
	size_t len = std::max(this->values.size(), other.values.size());
	for(size_t i = 0; i < len; ++i){
		if(this->get(i) != other.get(i)){
			return false;
		}
	}
	return true;
}

std::ostream& operator<<(std::ostream& os, const Vector& rhs){
	os << "(";
	for(size_t i = 0; i < rhs.values.size(); ++i){
		os << rhs.values[i];
		if(i != rhs.values.size()-1){
			os << ", ";
		}
	}
	os << ")";
	return os;
}

}
