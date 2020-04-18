/**
 * @file Unefunge93Strategy.cpp
 * Strategy for Unefunge-93 commands.
 * @author Conlan Wesson
 */

#include "Unefunge93Strategy.h"
#include <iostream>

namespace Funge {


Unefunge93Strategy::Unefunge93Strategy(Field& f, InstructionPointer& i, StackStack& s) :
	FungeStrategy(f, i, s)
{
	
}

bool Unefunge93Strategy::execute(inst_t cmd){
	if(cmd >= '0' && cmd <= '9'){
		stack.top().push(cmd-'0');
	}else{
		switch(cmd){
			case '@':
				ip.stop(); break;
			case '#':
				ip.next(); break;
			
			// Operators
			case '!':
				if(stack.top().pop() == 0){
					stack.top().push(1);
				}else{
					stack.top().push(0);
				}
				break;
			case '%':{
				stack_t a = stack.top().pop();
				stack_t b = stack.top().pop();
				stack.top().push(b%a);
			} break;
			case '*':{
				stack_t a = stack.top().pop();
				stack_t b = stack.top().pop();
				stack.top().push(a*b);
			} break;
			case '+':{
				stack_t a = stack.top().pop();
				stack_t b = stack.top().pop();
				stack.top().push(a+b);
			} break;
			case '-':{
				stack_t a = stack.top().pop();
				stack_t b = stack.top().pop();
				stack.top().push(b-a);
			} break;
			case '/':{
				stack_t a = stack.top().pop();
				stack_t b = stack.top().pop();
				stack.top().push(b/a);
			} break;
			case '`':{
				stack_t a = stack.top().pop();
				stack_t b = stack.top().pop();
				if(b > a){
					stack.top().push(1);
				}else{
					stack.top().push(0);
				}
			} break;
			
			// Output
			case ',':{
				stack_t x = stack.top().pop();
				if(x == 10){
					std::cout << std::endl;
				}else{
					std::cout << static_cast<char>(x);
				}
			} break;
			case '.':{
				stack_t x = stack.top().pop();
				std::cout << static_cast<int>(x) << ' ';
			} break;
			
			//Input
			case '&':{
				stack_t num = 0;
				char c = getchar();
				while(c < '0' || c > '9'){
					c = getchar();
				}
				while(c >= '0' && c <= '9'){
					num = (num*10) + (c-'0');
					c = getchar();
				}
				ungetc(c, stdin);
				stack.top().push(num);
			} break;
			case '~':{
				int q = getchar();
				if(q == 13){
					q = getchar();
				}
				stack.top().push(q);
			} break;
			
			// Stack operations
			case '$':
				stack.top().pop(); break;
			case ':':{
				stack_t x = stack.top().pop();
				stack.top().push(x);
				stack.top().push(x);
			} break;
			case '\\':{
				stack_t a = stack.top().pop();
				stack_t b = stack.top().pop();
				stack.top().push(a);
				stack.top().push(b);
			} break;
			
			// Flow Control
			case '<':
				ip.setDelta(Vector{-1}); break;
			case '>':
				ip.setDelta(Vector{1}); break;
			case '?':{
				int s = field.dimensions()*2;
				int r = random()%s;
				Vector v;
				if(r & 1){
					v.set(r>>1, -1);
				}else{
					v.set(r>>1, 1);
				}
				ip.setDelta(v);
				break;
			}
			case '_':
				if(stack.top().pop() == 0){
					ip.setDelta(Vector{1});
				}else{
					ip.setDelta(Vector{-1});
				}
				break;
				
			//Self-Modifying
			case 'g':{
				stack_t gy = stack.top().pop();
				stack_t gx = stack.top().pop();
				stack.top().push(static_cast<stack_t>(field.get(Vector{gx,gy})));
			} break;
			case 'p':{
				stack_t y = stack.top().pop();
				stack_t x = stack.top().pop();
				stack_t v = stack.top().pop();
				field.set(Vector{x,y}, v);
			} break;
			
			default:
				return false;
		}
	}
	return true;
}

}
