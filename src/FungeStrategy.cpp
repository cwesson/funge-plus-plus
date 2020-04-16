/**
 * @file FungeStrategy.cpp
 * Strategy for executing Funge commands.
 * @author Conlan Wesson
 */

#include "FungeStrategy.h"

namespace Funge {

FungeStrategy::FungeStrategy(Field& f, InstructionPointer& i, StackStack& s) :
	field(f),
	ip(i),
	stack(s)
{
	
}


}
