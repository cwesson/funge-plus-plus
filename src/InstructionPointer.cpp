/**
 * @file InstructionPointer.cpp
 * Stores all information needed to track the instructions.
 * @author Conlan Wesson
 */

#include "InstructionPointer.h"
#include "FungeUniverse.h"
#include "FungeRunner.h"
#include "Field.h"

namespace Funge {

InstructionPointer::InstructionPointer(FungeRunner& r) :
	runner(r),
	stopped(false),
	pos({0}),
	delta({1}),
	storage({0})
{
	
}

InstructionPointer::InstructionPointer(const InstructionPointer& orig, FungeRunner& r) :
	runner(r),
	stopped(orig.stopped),
	pos(orig.pos),
	delta(orig.delta),
	storage(orig.storage)
{
	
}

inst_t InstructionPointer::get() const{
	return runner.getField()[pos];
}

void InstructionPointer::set(inst_t i){
	runner.getField().put(pos, i);
}

bool InstructionPointer::inField(const Field& field) const {
	for(size_t n = 0; n < runner.getUniverse().dimensions(); ++n){
		if(pos.get(n) < field.min(n) || pos.get(n) > field.max(n)){
			return false;
		}
	}
	return true;
}

void InstructionPointer::next(){
	if(!stopped){
		pos += delta;
		const Field& field = runner.getField();
		if(runner.getUniverse().topology() == TOPO_TORUS){
			if(pos.get(0) > 80){
				pos.set(0, 0);
			}else if(pos.get(0) < 0){
				pos.set(0, 79);
			}
			if(pos.get(1) > 25){
				pos.set(1, 0);
			}else if(pos.get(1) < 0){
				pos.set(1, 24);
			}
		}else{
			if(!inField(field)){
				delta.reverse();
				pos += delta;
				while(inField(field)){
					pos += delta;
				}
				delta.reverse();
				pos += delta;
			}
		}
	}
}

void InstructionPointer::setPos(const Vector& v){
	pos = v;
}

void InstructionPointer::setDelta(const Vector& v){
	if(runner.getUniverse().isMode(FUNGE_MODE_HOVER)){
		size_t size = std::max(delta.size(), v.size());
		for(size_t i = 0; i < size; ++i){
			delta.set(i, delta.get(i) + v.get(i));
		}
	}else{
		delta = v;
	}
}

void InstructionPointer::setStorage(const Vector& v){
	storage = v;
}

void InstructionPointer::reflect(){
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

bool InstructionPointer::isStopped() const{
	return stopped;
}

const Vector& InstructionPointer::getPos() const{
	return pos;
}

const Vector& InstructionPointer::getDelta() const{
	return delta;
}

const Vector& InstructionPointer::getStorage() const{
	return storage;
}

std::ostream& operator<<(std::ostream& os, const InstructionPointer& rhs){
	os << rhs.pos;
	return os;
}

}
