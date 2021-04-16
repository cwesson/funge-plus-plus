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
	normalize();
}

Vector::Vector(std::initializer_list<dim_t> v) : values(v){
	normalize();
}

Vector& Vector::operator=(const Vector& orig){
	values.clear();
	values = orig.values;
	normalize();
	return *this;
}

Vector& Vector::operator=(std::initializer_list<dim_t> orig){
	values.clear();
	values = orig;
	normalize();
	return *this;
}

void Vector::normalize(){
	while(values.size() > 1 && values.back() == 0){
		values.pop_back();
	}
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
	normalize();
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

Vector& Vector::operator-=(const Vector& other){
	size_t len = std::max(this->values.size(), other.values.size());
	for(size_t i = 0; i < len; ++i){
		this->set(i, this->get(i)-other.get(i));
	}
	return *this;
}

Vector operator-(const Vector& lhs, const Vector& rhs) {
	return Vector(lhs) -= rhs;
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

bool Vector::operator<=(const Vector& other) const{
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
	return true;
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

bool Vector::operator!=(const Vector& other) const{
	return !(*this == other);
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

std::istream& operator>>(std::istream& is, Vector& rhs){
	rhs.values.clear();
	char c;
	is >> c;
	if(c == '('){
		is >> c;
		size_t d = 0;
		dim_t v = 0;
		bool neg = false;
		while(c != ')'){
			if(isdigit(c)){
				v = (v*10)+(c-'0');
			}else if(c == ','){
				if(neg){
					v = -v;
				}
				rhs.set(d, v);
				++d;
				v = 0;
				neg = false;
			}else if(v == 0 && c == '-'){
				neg = true;
			}else if(!isspace(c)){
				is.unget();
				break;
			}
			is >> c;
		}
		if(neg){
			v = -v;
		}
		rhs.set(d, v);
	}else{
		is.unget();
	}
	rhs.normalize();
	return is;
}

}
