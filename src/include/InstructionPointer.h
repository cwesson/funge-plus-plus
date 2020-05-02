/**
 * @file InstructionPointer.h
 * Stores all information needed to track the instructions.
 * @author Conlan Wesson
 */

#pragma once

#include "Vector.h"
#include "Field.h"
#include "funge_types.h"

namespace Funge {

class InstructionPointer {
	public:
		explicit InstructionPointer(Field& f);
		InstructionPointer(const InstructionPointer& orig);
		
		inst_t get() const;
		void set(inst_t i);
		void setPos(const Vector& v);
		void setDelta(const Vector& v);
		void setStorage(const Vector& v);
		void reverse();
		void left();
		void right();
		
		void stop();
		bool isStopped();
		
		void next();
		
		const Vector& getPos() const;
		const Vector& getDelta() const;
		const Vector& getStorage() const;
		
		friend std::ostream& operator<<(std::ostream& os, const InstructionPointer& rhs);
	
	private:
		bool stopped;
		Vector pos;
		Vector delta;
		Vector storage;
		Field& field;
		
		bool inField();
};

}
