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
		Defunge(const Defunge& orig) = delete;
		Defunge operator=(const Defunge& orig) = delete;
		virtual ~Defunge() = default;

		void debug(FungeDebugger* dbg, FungeRunner* run);

	private:
		enum Error {
			DEFUNGE_OK,
			DEFUNGE_BREAK,
			DEFUNGE_NO_THREAD,
		};

		typedef Error (Defunge::*debugger_command_t)(std::istringstream&);

		std::recursive_mutex mutex;
		FungeDebugger* debugger;
		FungeRunner* runner;
		std::map<std::string, debugger_command_t> cmdMap;

		Defunge();

		void debugWrite(const Field& field, const Vector& pos, inst_t inst);
		void printIP(const FungeRunner& ip);
		void printField(FungeDebugger* dbg, const Field& field, const Vector& center, const Vector& size, const Vector& dim, const InstructionPointer* ip);

		Error runCommand(std::istringstream& iss);
		Error quitCommand(std::istringstream& iss);
		Error stepCommand(std::istringstream& iss);
		Error peekCommand(std::istringstream& iss);
		Error deltaCommand(std::istringstream& iss);
		Error storageCommand(std::istringstream& iss);
		Error positionCommand(std::istringstream& iss);
		Error threadCommand(std::istringstream& iss);
		Error backtraceCommand(std::istringstream& iss);
		Error setdeltaCommand(std::istringstream& iss);
		Error setposCommand(std::istringstream& iss);
		Error getCommand(std::istringstream& iss);
		Error listCommand(std::istringstream& iss);
		Error breakCommand(std::istringstream& iss);
		Error watchCommand(std::istringstream& iss);
		Error readCommand(std::istringstream& iss);
		Error universeCommand(std::istringstream& iss);
};

}
