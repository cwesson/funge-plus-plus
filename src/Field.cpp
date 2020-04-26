/**
 * @file Field.cpp
 * Represents the instructions in Funge-space.
 * @author Conlan Wesson
 */

#include "Field.h"
#include "FungeConfig.h"
#include <limits>

namespace Funge{

Field::Field(std::istream& file, size_t dim){
	parse(Vector{0}, file);
	//std::cout << *this << std::endl;
	if(dim == 0){
		funge_config.dimensions = maxs.size();
	}else{
		funge_config.dimensions = dim;
	}
}

Vector Field::parse(const Vector& start, std::istream& file, bool binary){
	Vector v(start);
	Vector max(start);
	int last = 0;
	for(int i = file.get(); !file.eof(); i = file.get()) {
		if(!binary && (i == '\n' || i == '\r')){
			if(i == '\r'){
				int j = file.peek();
				if(j == '\n'){
					file.get();
				}
			}
			if(last != '\f'){
				increment(1, v, max);    // ++y
				reset(0, v, start, max); // x = 0
			}
		}else if(!binary && (i == '\f')){
			reset(0, v, start, max); // x = 0
			reset(1, v, start, max); // y = 0
			increment(2, v, max);    // ++z
			last = '\f';
		}else{
			if(i != ' '){
				set(v, i);
			}
			increment(0, v, max); // ++x
			last = i;
		}
	}
	return max-start;
}

void Field::dump(const Vector& start, const Vector& delta, std::ostream& file, bool binary){
	Vector v(start);
	Vector end(start+delta);
	std::vector<char> buffer;
	while(v < end){
		inst_t i = get(v);
		buffer.push_back(static_cast<char>(i));
		if(i != ' '){
			for(char c : buffer){
				file << c;
			}
			buffer.clear();
		}
		v.set(0, v[0]+1); // ++x
		if(v[0] >= end[0]){
			if(!binary){
				file << '\n';
				v.set(1, v[1]+1);   // ++y
				v.set(0, start[0]); // x = 0
			}else{
				break;
			}
		}
		if(v[1] >= end[1]){
			break;
		}
	}
}

void Field::increment(dim_t d, Vector& v, Vector& max){
	v.set(d, v[d]+1);
	if(v[d] > max[d]){
		max.set(d, v[d]);
	}
}

void Field::reset(dim_t d, Vector& v, const Vector& start, Vector& max){
	if(v[d] > max[d]){
		max.set(d, v[d]);
	}
	v.set(d, start[d]);
}

dim_t Field::min(size_t d) const{
	dim_t ret = 0;
	if(d < mins.size()){
		ret = mins[d];
	}
	return ret;
}

dim_t Field::max(size_t d) const{
	dim_t ret = 0;
	if(d < maxs.size()){
		ret = maxs[d];
	}
	return ret;
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
	if(funge_config.standard == 93){
		field[p] = static_cast<char>(v);
	}else{
		field[p] = v;
	}
}

inst_t Field::get(const Vector& p) const{
	inst_t ret = ' ';
	auto find = field.find(p);
	if(find != field.end()){
		ret = find->second;
	}
	if(funge_config.standard == 93){
		return static_cast<char>(ret);
	}else{
		return ret;
	}
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
