/**
 * @file FungeStateNormal.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeStateNormal.h"
#include "FungeRunner.h"
#include "FungeConfig.h"
#include "Unefunge93Strategy.h"
#include "Unefunge98Strategy.h"
#include "Befunge93Strategy.h"
#include "Befunge98Strategy.h"
#include "Trefunge98Strategy.h"

namespace Funge {

FungeStateNormal::FungeStateNormal(FungeRunner& r, Field& f, StackStack& s, InstructionPointer& i) :
	FungeState(r, s),
	strategy(NULL)
{
	switch(funge_config.dimensions){
		case 1:
			switch (funge_config.standard)
			{
				case 93:
					strategy = new Unefunge93Strategy(f, i, s);
					break;
				case 98:
					strategy = new Unefunge98Strategy(f, i, s);
					break;
				default:
					break;
			}
			break;
		case 2:
			switch (funge_config.standard)
			{
				case 93:
					strategy = new Befunge93Strategy(f, i, s);
					break;
				case 98:
					strategy = new Befunge98Strategy(f, i, s);
					break;
				default:
					break;
			}
			break;
		case 3:
			switch (funge_config.standard)
			{
				case 98:
					strategy = new Trefunge98Strategy(f, i, s);
					break;
				default:
					break;
			}
			break;
	}
}

FungeStateNormal::~FungeStateNormal(){
	delete strategy;
}

bool FungeStateNormal::execute(inst_t i){
	if(i == ' '){
		return false;
	}else if(i == '\"'){
		runner.setState(runner.getStringState());
	}else{
		return strategy->execute(i);
	}
	return true;
}

}
