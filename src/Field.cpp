/**
 * @file Field.cpp
 * Represents the instructions in Funge-space.
 * @author Conlan Wesson
 */

#include "Field.h"
#include "FungeUniverse.h"
#include <limits>
#include <string>
#include <sstream>

namespace Funge{

Field::Field(std::istream& file, FileFormat fmt, size_t dim, FungeUniverse& uni) :
	universe(uni),
	field(),
	maxs(),
	mins(),
	planes()
{
	switch(fmt){
		default:
		case FORMAT_BF:
			parse(Vector{0}, file);
			break;
		case FORMAT_BEQ:
			parseBeq(file);
			break;
		case FORMAT_FL:
			parseFungeLib(file);
			break;
	}
	if(dim == 0){
		universe.dimensions(maxs.size());
	}else{
		universe.dimensions(dim);
	}
}

Field::Field(size_t dim, FungeUniverse& uni) :
	universe(uni),
	field(),
	maxs(),
	mins(),
	planes()
{
	if(dim == 0){
		universe.dimensions(maxs.size());
	}else{
		universe.dimensions(dim);
	}
}

Vector Field::parse(const Vector& start, std::istream& file, bool binary){
	Vector v(start);
	Vector max(start);
	int last = 0;
	for(int i = file.get(); !file.eof(); i = file.get()) {
		size_t dimensions = universe.dimensions();
		if((i == '\n' || i == '\r') && !binary){
			if(i == '\r'){
				int j = file.peek();
				if(j == '\n'){
					file.get();
				}
			}
			if(last != '\f' && last != '\v'){
				increment(1, v, max);    // ++y
				reset(0, v, start, max); // x = 0
			}
		}else if((i == '\f') && !binary){
			if(dimensions == 0 || dimensions >= 3){
				reset(0, v, start, max); // x = 0
				reset(1, v, start, max); // y = 0
				increment(2, v, max);    // ++z
				last = '\f';
			}
		}else if((i == '\v') && !binary){
			if(dimensions == 0 || dimensions >= 3){
				reset(0, v, start, max); // x = 0
				reset(1, v, start, max); // y = 0
				reset(2, v, start, max); // z = 0
				increment(3, v, max);    // ++d4
				last = '\v';
			}
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

std::vector<std::string> splitString(std::string str, char delim){
	std::vector<std::string> ret;
	auto iss = std::istringstream(str);
	while(iss.good()){
		std::string substr;
		std::getline(iss, substr, delim);
		ret.push_back(substr);
	}
	return ret;
}

void Field::parseBeq(std::istream& file){
	size_t dims = 0;
	while(file.good()){
		std::string line;
		std::getline(file, line);
		auto ctrl = splitString(line, ',');
		size_t lines = 0;
		Vector origin;
		size_t dim = 0;
		for(auto c : ctrl){
			auto cmd = splitString(c, ' ');
			if(cmd[0] == "Version"){
				// ok
			}else if(cmd[0] == "Dimensions"){
				if(dims == 0){
					dims = std::stoul(cmd[1]);
				}else{
					std::cerr << "Unexpected dimensions" << std::endl;
				}
			}else if(cmd[0] == "Lines"){
				lines = std::stoul(cmd[1]);
			}else if(cmd[0] == "Origin"){
				auto orig = splitString(cmd[1], ':');
				for(dim = 0; dim < orig.size(); ++dim){
					origin.set(dim, std::stoi(orig[dim]));
				}
			}else if(cmd[0] == "Coord"){
				auto orig = splitString(cmd[1], ':');
				size_t start = dim;
				for( ; dim < orig.size()+start; ++dim){
					if(orig[dim-start].size() > 0){
						origin.set(dim, std::stoi(orig[dim-start]));
					}
				}
			}
		}
		if(lines > 0){
			Vector pos(origin);
			for(size_t i = 0; i < lines; ++i){
				std::getline(file, line);
				for(auto c : line){
					set(pos, c);
					pos.set(0, pos.get(0)+1); // ++x
				}
				pos.set(0, origin.get(0)); // x=0
				pos.set(1, pos.get(1)+1);  // ++y
			}
		}
	}
	if(universe.dimensions() == 0){
		if(dims == 0){
			dims = maxs.size();
		}
		universe.dimensions(dims);
	}
}

void Field::parseFungeLib(std::istream& file){
	universe.dimensions(3);
	Vector pos;
	while(file.good()){
		std::string line;
		std::getline(file, line);
		if(line.length() == 2 && line[0] == '='){
			char ext = line[1];
			if(ext >= 'A' && ext <= 'Z'){
				pos = {0, 0, (ext - 'A')};
				planes.push_back(ext);
				continue;
			}
		}

		for(char i : line){
			set(pos, i);
			pos += Vector{1};
		}
		pos += Vector{0, 1};  // ++y
		pos.set(0, 0);        // x=0
	}
}

void Field::dump(const Vector& start, const Vector& delta, std::ostream& file, bool binary) const {
	Vector v(start);
	Vector end(start+delta);
	std::vector<char> buffer;
	while(v < end){
		inst_t i = get(v);
		buffer.push_back(static_cast<char>(i));
		if(i != ' ' || binary){
			for(char c : buffer){
				file << c;
			}
			buffer.clear();
		}
		v.set(0, v[0]+1); // ++x
		if(v[0] >= end[0]){
			file << '\n';
			if(!binary){
				buffer.clear();
			}
			v.set(1, v[1]+1);   // ++y
			v.set(0, start[0]); // x = 0
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

FungeTopo Field::topology() const{
	return universe.topology();
}

size_t Field::dimensions() const{
	return universe.dimensions();
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

FungeUniverse& Field::getUniverse(){
	return universe;
}

void Field::set(const Vector& p, inst_t v){
	while(maxs.size() < p.size()){
		maxs.push_back(0);
	}
	while(mins.size() < p.size()){
		mins.push_back(0);
	}
	universe.getDebugger().write(*this, p, v);
	if(v == ' '){
		auto find = field.find(p);
		if(find != field.end()){
			field.erase(find);
		}
		for(size_t i = 0; i < p.size(); ++i){
			if(maxs[i] == p[i]){
				// scan for new max
				dim_t max = std::numeric_limits<dim_t>::min() ;
				for(auto s = field.cbegin(); s != field.cend(); ++s){
					if(s->first[i] > max){
						max = s->first[i];
					}
				}
				maxs[i] = max;
			}
			if(mins[i] == p[i]){
				// scan for new min
				dim_t min = std::numeric_limits<dim_t>::max();
				for(auto s = field.cbegin(); s != field.cend(); ++s){
					if(s->first[i] < min){
						min = s->first[i];
					}
				}
				mins[i] = min;
			}
		}
	}else{
		for(size_t i = 0; i < p.size(); ++i){
			if(maxs[i] < p[i]){
				maxs[i] = p[i];
			}
			if(mins[i] > p[i]){
				mins[i] = p[i];
			}
		}
		if(universe.cellSize() == CELL_CHAR){
			field[p] = static_cast<char>(v);
		}else{
			field[p] = v;
		}
	}
}

inst_t Field::get(const Vector& p) const{
	inst_t ret = ' ';
	auto find = field.find(p);
	if(find != field.end()){
		ret = find->second;
	}
	if(universe.cellSize() == CELL_CHAR){
		return static_cast<char>(ret);
	}else{
		return ret;
	}
}

inst_t Field::operator[](const Vector& v) const{
	return get(v);
}

const std::vector<inst_t>& Field::hasPlanes() const{
	return planes;
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
