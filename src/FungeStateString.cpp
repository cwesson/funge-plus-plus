/**
 * @file FungeStateString.cpp
 * Controls execution of a single IP.
 * @author Conlan Wesson
 */

#include "FungeStateString.h"
#include "FungeRunner.h"
#include "FungeConfig.h"

namespace Funge {

FungeStateString::FungeStateString(FungeRunner& r) :
	FungeState(r),
	end('\"'),
	previous('\0')
{
	
}

void FungeStateString::escape(inst_t i){
	stack_t code = i;
	switch(i){
		case '0':
			code = '\0';
			break;
		case 'a':
			code = '\a';
			break;
		case 'b':
			code = '\b';
			break;
		case 't':
			code = '\t';
			break;
		case 'n':
			code = '\n';
			break;
		case 'v':
			code = '\v';
			break;
		case 'f':
			code = '\f';
			break;
		case 'r':
			code = '\r';
			break;
		case 'e':
			code = '\e';
			break;
		default:
			code = i;
			break;
	}
	stack.top().push(code);
}

bool FungeStateString::execute(inst_t i){
	if(i == end){
		previous = '\0';
		runner.setState(runner.getNormalState());
	}else{
		switch(funge_config.strings){
			case STRING_MULTISPACE:
				stack.top().push(static_cast<stack_t>(i));
				break;
			case STRING_SGML:
				if(i != ' ' || previous != ' '){
					stack.top().push(static_cast<stack_t>(i));
					previous = i;
				}else{
					return false;
				}
				break;
			case STRING_C:
				if(i == '\\'){
					ip.next();
					escape(ip.get());
				}else{
					stack.top().push(static_cast<stack_t>(i));
				}
				break;
			default:
				return false;
		}
	}
	return true;
}

void FungeStateString::setEnd(inst_t i){
	end = i;
}

}
