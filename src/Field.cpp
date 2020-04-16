/**
 * @file Field.cpp
 * Represents the instructions in Funge-space.
 * @author Conlan Wesson
 */

#include "Field.h"

namespace Funge{

Field::Field(std::istream& file){
	dim_t x = 0;
	dim_t y = 0;
	dim_t z = 0;
	for(int i = file.get(); !file.eof(); i = file.get()) {
		if(i == '\n' || i == '\r'){
			if(i == '\r'){
				int j = file.peek();
				if(j == '\n'){
					file.get();
				}
			}
			++y;
			x = 0;
		}else if(i == '\f'){
			x = 0;
			y = 0;
			++z;
		}else{
			if(i != ' '){
				set(Vector{x, y}, i);
			}
			++x;
		}
	}
}

size_t Field::dimensions() const{
	return maxs.size();
}

dim_t Field::min(size_t d) const{
	return mins[d];
}

dim_t Field::max(size_t d) const{
	return maxs[d];
}

void Field::set(const Vector& p, inst_t v){
	while(maxs.size() < p.size()){
		maxs.push_back(0);
	}
	while(mins.size() < p.size()){
		mins.push_back(0);
	}
	for(size_t i = 0; i < p.size(); ++i){
		if(maxs[i] < p[i]){
			maxs[i] = p[i];
		}
		if(mins[i] > p[i]){
			mins[i] = p[i];
		}
	}
	for(auto pair : field){
		if(pair.first == p){
			field[p] = v;
			return;
		}
	}
	field.insert(std::pair<Vector, inst_t>(p, v));
}

inst_t Field::get(const Vector& p) const{
	inst_t ret = ' ';
	for(auto pair : field){
		if(pair.first == p){
			ret = pair.second;
		}
	}
	return ret;
}

inst_t Field::operator[](const Vector& v) const{
	return get(v);
}

std::ostream& operator<<(std::ostream& os, const Field& rhs){
	for(dim_t i = rhs.min(1); i <= rhs.max(1); ++i){
		for(dim_t j = rhs.min(0); j <= rhs.max(0); ++j){
			Vector v{j, i};
			//os << v;
			os << rhs.get(v);
		}
		os << std::endl;
	}
	return os;
}

}
