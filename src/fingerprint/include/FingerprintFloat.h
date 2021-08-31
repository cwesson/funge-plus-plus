/**
 * @file FingerprintFloat.h
 * Double and single precision floating point.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include "FungeUtilities.h"
#include <iomanip>

namespace Funge {

template <typename T>
class FingerprintFloat : public Fingerprint {
	static_assert(sizeof(T) <= sizeof(stack_t));
	public:
		FingerprintFloat(Field& f, InstructionPointer& i, StackStack& s) :
			Fingerprint(f, i, s, {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
					'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'X', 'Y'})
		{}

		virtual ~FingerprintFloat() = default;
		
		virtual bool execute(inst_t cmd) override {
			switch(cmd){
				case 'A':{
					T b = stackToT(stack.top().pop());
					T a = stackToT(stack.top().pop());
					T n = a + b;
					stack.top().push(TToStack(n));
				} break;
				case 'B':{
					T n = stackToT(stack.top().pop());
					n = std::sin(n);
					stack.top().push(TToStack(n));
				} break;
				case 'C':{
					T n = stackToT(stack.top().pop());
					n = std::cos(n);
					stack.top().push(TToStack(n));
				} break;
				case 'D':{
					T b = stackToT(stack.top().pop());
					T a = stackToT(stack.top().pop());
					T n = a / b;
					stack.top().push(TToStack(n));
				} break;
				case 'E':{
					T n = stackToT(stack.top().pop());
					n = std::asin(n);
					stack.top().push(TToStack(n));
				} break;
				case 'F':{
					T n = static_cast<T>(stack.top().pop());
					stack.top().push(TToStack(n));
				} break;
				case 'G':{
					T n = stackToT(stack.top().pop());
					n = std::atan(n);
					stack.top().push(TToStack(n));
				} break;
				case 'H':{
					T n = stackToT(stack.top().pop());
					n = std::acos(n);
					stack.top().push(TToStack(n));
				} break;
				case 'I':{
					T n = stackToT(stack.top().pop());
					stack.top().push(static_cast<stack_t>(n));
				} break;
				case 'K':{
					T n = stackToT(stack.top().pop());
					n = std::log(n);
					stack.top().push(TToStack(n));
				} break;
				case 'L':{
					T n = stackToT(stack.top().pop());
					n = std::log10(n);
					stack.top().push(TToStack(n));
				} break;
				case 'M':{
					T b = stackToT(stack.top().pop());
					T a = stackToT(stack.top().pop());
					T n = a * b;
					stack.top().push(TToStack(n));
				} break;
				case 'N':{
					T n = stackToT(stack.top().pop());
					n = -n;
					stack.top().push(TToStack(n));
				} break;
				case 'P':{
					T n = stackToT(stack.top().pop());
					std::cout << std::fixed << std::setprecision(6) << n << ' ';
				} break;
				case 'Q':{
					T n = stackToT(stack.top().pop());
					n = std::sqrt(n);
					stack.top().push(TToStack(n));
				} break;
				case 'R':{
					std::string s = popString(stack.top());
					double d = std::stod(s);
					T n = static_cast<T>(d);
					stack.top().push(TToStack(n));
				} break;
				case 'S':{
					T b = stackToT(stack.top().pop());
					T a = stackToT(stack.top().pop());
					T n = a - b;
					stack.top().push(TToStack(n));
				} break;
				case 'T':{
					T n = stackToT(stack.top().pop());
					n = std::tan(n);
					stack.top().push(TToStack(n));
				} break;
				case 'V':{
					T n = stackToT(stack.top().pop());
					n = std::abs(n);
					stack.top().push(TToStack(n));
				} break;
				case 'X':{
					T n = stackToT(stack.top().pop());
					n = std::exp(n);
					stack.top().push(TToStack(n));
				} break;
				case 'Y':{
					T y = stackToT(stack.top().pop());
					T x = stackToT(stack.top().pop());
					T n = std::pow(x, y);
					stack.top().push(TToStack(n));
				} break;
				default:
					return false;
			}
			return true;
		}

	private:
		T stackToT(stack_t n){
			return *reinterpret_cast<T*>(&n);
		}

		stack_t TToStack(T n){
			return *reinterpret_cast<stack_t*>(&n);
		}
};

}
