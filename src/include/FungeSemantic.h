/**
 * @file FungeSemantic.h
 * Type declaration for semantics.
 * @author Conlan Wesson
 */

#pragma once

#include <functional>

namespace Funge {

class FungeSemantic {
	public:
		enum SemanticFlags {
			NONE,
			MOVEMENT,
		};

		explicit FungeSemantic(std::function<FungeError()> sem) :
			func(sem),
			flags(NONE)
		{}

		FungeSemantic(std::function<FungeError()> sem, SemanticFlags flg) :
			func(sem),
			flags(flg)
		{}

		FungeError operator()(){
			return func();
		}

		bool isMovement(){
			return flags == MOVEMENT;
		}
	
	private:
		std::function<FungeError()> func;
		SemanticFlags flags;
};

}
