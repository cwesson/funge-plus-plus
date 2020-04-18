/**
 * @file InstructionPointer.cpp
 * Stores all information needed to track the instructions.
 * @author Conlan Wesson
 */

#include "InstructionPointer.h"
#include "FungeConfig.h"

namespace Funge {

InstructionPointer::InstructionPointer(Field& f) :
	stopped(false),
	pos({0}),
	delta({1}),
	field(f)
{
	
}

InstructionPointer::InstructionPointer(const InstructionPointer& orig) :
	stopped(orig.stopped),
	pos(orig.pos),
	delta(orig.delta),
	field(orig.field)
{
	
}

inst_t InstructionPointer::get() const{
	return field[pos];
}

void InstructionPointer::set(inst_t i){
	field.set(pos, i);
}

bool InstructionPointer::inField(){
	for(size_t n = 0; n < funge_config.dimensions; ++n){
		if(pos.get(n) < field.min(n) || pos.get(n) > field.max(n)){
			return false;
		}
	}
	return true;
}

void InstructionPointer::next(){
	if(!stopped){
		pos += delta;
		if(!inField()){
			delta.reverse();
			pos += delta;
			while(inField()){
				pos += delta;
			}
			delta.reverse();
			pos += delta;
		}
	}
}

void InstructionPointer::setDelta(const Vector& v){
	delta = v;
}

void InstructionPointer::reverse(){
	delta.reverse();
}

void InstructionPointer::left(){
	delta.left();
}

void InstructionPointer::right(){
	delta.right();
}

void InstructionPointer::stop(){
	stopped = true;
}

bool InstructionPointer::isStopped(){
	return stopped;
}

const Vector& InstructionPointer::getPos() const{
	return pos;
}

const Vector& InstructionPointer::getDelta() const{
	return delta;
}

std::ostream& operator<<(std::ostream& os, const InstructionPointer& rhs){
	os << rhs.pos;
	return os;
}

}
