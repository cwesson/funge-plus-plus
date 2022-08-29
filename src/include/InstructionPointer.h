/**
 * @file InstructionPointer.h
 * Stores all information needed to track the instructions.
 * @author Conlan Wesson
 */

#pragma once

#include "Vector.h"
#include "funge_types.h"
#include <functional>

namespace Funge {
class FungeRunner;
class Field;

/**
 * Stores the position, movement delta, and storage offset.
 */
class InstructionPointer {
	public:
		/**
		 * Constructor.
		 * @param r Runner the IP belongs to.
		 */
		explicit InstructionPointer(FungeRunner& r);

		/**
		 * Copy constructor.
		 */
		InstructionPointer(const InstructionPointer& orig) = delete;

		/**
		 * Copy constructor.
		 * @param orig Ip to copy.
		 * @param r Runner the IP belongs to.
		 */
		InstructionPointer(const InstructionPointer& orig, FungeRunner& r);
		
		/**
		 * Get the instruction at the IP.
		 * @return Instruction at the current IP position.
		 */
		inst_t get() const;

		/**
		 * Put the instruction at the IP.
		 * @param i Instruction to set at the current IP position.
		 */
		void put(inst_t i);

		/**
		 * Set the IP position.
		 * @param v New position.
		 */
		void setPos(const Vector& v);

		/**
		 * Set the IP movement delta.
		 * @param v New movement delta.
		 */
		void setDelta(const Vector& v);

		/**
		 * Set the IP storage offset.
		 * @param v New storage offset.
		 */
		void setStorage(const Vector& v);

		/**
		 * Reflect the IP movement delta.
		 */
		void reflect();

		/**
		 * Turn the IP movement delta left.
		 */
		void left();

		/**
		 * Turn the IP movement delta right.
		 */
		void right();

		/**
		 * Stop the IP movement delta.
		 */
		void stop();

		/**
		 * Determine if the IP is stopped.
		 * @return true if the IP is stopped, false otherwise.
		 */
		bool isStopped() const;

		/**
		 * Advance the IP to the next position.
		 */
		void next();

		/**
		 * Get the current IP position.
		 * @return Current postion.
		 */
		const Vector& getPos() const;

		/**
		 * Get the current IP movement delta.
		 * @return Current movement delta.
		 */
		const Vector& getDelta() const;

		/**
		 * Get the current IP storage offset.
		 * @return Current storage offset.
		 */
		const Vector& getStorage() const;

		/**
		 * Add a movement change observer.
		 * @param cb Function to call on movement cahnges.
		 */
		void addObserver(std::function<void(const Vector&)> cb);

		/**
		 * Output stream operator.
		 * @param os Output stream.
		 * @param rhs IP to output.
		 * @return Output stream.
		 */
		friend std::ostream& operator<<(std::ostream& os, const InstructionPointer& rhs);
	
	private:
		std::vector<std::function<void(const Vector&)>> observers;
		FungeRunner& runner;
		bool stopped;
		Vector pos;
		Vector delta;
		Vector storage;
		
		bool inField(const Field& field) const;
};

}
