/**
 * @file InstructionPointer.h
 * Stores all information needed to track the instructions.
 * @author Conlan Wesson
 */

#pragma once

#include "Vector.h"
#include "funge_types.h"

namespace Funge {
class FungeRunner;
class Field;

class InstructionPointer {
	public:
		explicit InstructionPointer(FungeRunner& r);
		InstructionPointer(const InstructionPointer& orig) = delete;
		InstructionPointer(const InstructionPointer& orig, FungeRunner& r);
		
		inst_t get() const;
		void set(inst_t i);
		void setPos(const Vector& v);
		void setDelta(const Vector& v);
		void setStorage(const Vector& v);
		void reflect();
		void left();
		void right();
		
		void stop();
		bool isStopped() const;
		
		void next();
		
		const Vector& getPos() const;
		const Vector& getDelta() const;
		const Vector& getStorage() const;
		
		friend std::ostream& operator<<(std::ostream& os, const InstructionPointer& rhs);
	
	private:
		FungeRunner& runner;
		bool stopped;
		Vector pos;
		Vector delta;
		Vector storage;
		
		bool inField(const Field& field) const;
};

}
