/**
 * @file Defunge.h
 * Funge Debugger.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeDebugger.h"
#include <vector>

namespace Funge {

class Defunge {
	public:
		static Defunge& getInstance();
		virtual ~Defunge() = default;

		void debug(FungeDebugger* dbg, FungeRunner* runner);

	private:
		std::recursive_mutex mutex;

		Defunge();

		void debugWrite(const Field& field, const Vector& pos, inst_t inst);
		void printIP(const InstructionPointer* ip);
		void printField(FungeDebugger* dbg, const Field& field, const Vector& center, const Vector& size, const Vector& dim, const InstructionPointer* ip);
};

}
