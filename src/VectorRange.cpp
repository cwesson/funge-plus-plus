/**
 * @file VectorRange.cpp
 * Range iterator for Vectors.
 * @author Conlan Wesson
 */

#include "VectorRange.h"

namespace Funge {

VectorRange::VectorRange(const Vector& vfirst, const Vector& vlast) :
	vbegin(vfirst),
	vlast(vlast),
	vend(vlast),
	current(vfirst)
{
	if(vlast.get(0) >= vfirst.get(0)){
		vend.set(0, vlast.get(0)+1);
	}else{
		vend.set(0, vlast.get(0)-1);
	}
}

const Vector& VectorRange::begin(){
	return vbegin;
}

const Vector& VectorRange::end(){
	return vend;
}

Vector& VectorRange::operator*(){
	return current;
}

VectorRange& VectorRange::operator++(){
	dim_t len = std::max(vbegin.size(), vend.size());
	for(dim_t i = 0; i < len; ++i){
		dim_t n;
		if(vend.get(i) >= vbegin.get(i)){
			n = current.get(i)+1;
		}else{
			n = current.get(i)-1;
		}
		current.set(i, n);
		if(current == vend){
			break;
		}
		if(vlast.get(i) >= vbegin.get(i)){
			if(n > vlast.get(i)){
				current.set(i, vbegin.get(i));
			}else{
				break;
			}
		}else{
			if(n < vlast.get(i)){
				current.set(i, vbegin.get(i));
			}else{
				break;
			}
		}
	}
	return *this;
}

VectorRange VectorRange::operator++(int){
	return ++(*this);
}

}
