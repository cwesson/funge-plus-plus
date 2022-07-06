/**
 * @file FishStrategy.cpp
 * Strategy for ><> commands.
 * @author Conlan Wesson
 */

#include "FishStrategy.h"
#include "FungeRunner.h"
#include "FungeConfig.h"
#include "FungeUtilities.h"
#include "FungeUniverse.h"
#include <cstdio>
#include <termios.h>

namespace Funge {

FishStrategy::FishStrategy(FungeRunner& r) :
	FungeStrategy(r),
	regs()
{
	r.pushSemantic(' ', std::bind(&FishStrategy::instructionSkip, this));
	r.pushSemantic('0', std::bind(&FishStrategy::instructionPush, this,  0));
	r.pushSemantic('1', std::bind(&FishStrategy::instructionPush, this,  1));
	r.pushSemantic('2', std::bind(&FishStrategy::instructionPush, this,  2));
	r.pushSemantic('3', std::bind(&FishStrategy::instructionPush, this,  3));
	r.pushSemantic('4', std::bind(&FishStrategy::instructionPush, this,  4));
	r.pushSemantic('5', std::bind(&FishStrategy::instructionPush, this,  5));
	r.pushSemantic('6', std::bind(&FishStrategy::instructionPush, this,  6));
	r.pushSemantic('7', std::bind(&FishStrategy::instructionPush, this,  7));
	r.pushSemantic('8', std::bind(&FishStrategy::instructionPush, this,  8));
	r.pushSemantic('9', std::bind(&FishStrategy::instructionPush, this,  9));
	r.pushSemantic('a', std::bind(&FishStrategy::instructionPush, this, 10));
	r.pushSemantic('b', std::bind(&FishStrategy::instructionPush, this, 11));
	r.pushSemantic('c', std::bind(&FishStrategy::instructionPush, this, 12));
	r.pushSemantic('d', std::bind(&FishStrategy::instructionPush, this, 13));
	r.pushSemantic('e', std::bind(&FishStrategy::instructionPush, this, 14));
	r.pushSemantic('f', std::bind(&FishStrategy::instructionPush, this, 15));
	// Directions
	r.pushSemantic('>', std::bind(&FishStrategy::instructionRight, this));
	r.pushSemantic('<', std::bind(&FishStrategy::instructionLeft, this));
	r.pushSemantic('v', std::bind(&FishStrategy::instructionDown, this));
	r.pushSemantic('^', std::bind(&FishStrategy::instructionUp, this));
	// Mirrors
	r.pushSemantic('\\', std::bind(&FishStrategy::instructionMirror1, this));
	r.pushSemantic('/', std::bind(&FishStrategy::instructionMirror2, this));
	r.pushSemantic('|', std::bind(&FishStrategy::instructionMirrorVert, this));
	r.pushSemantic('_', std::bind(&FishStrategy::instructionMirrorHori, this));
	r.pushSemantic('#', std::bind(&FishStrategy::instructionMirrorAll, this));
	// Movement
	r.pushSemantic('x', std::bind(&FishStrategy::instructionRandom, this));
	r.pushSemantic('!', std::bind(&FishStrategy::instructionTrampoline, this));
	r.pushSemantic('?', std::bind(&FishStrategy::instructionConditional, this));
	r.pushSemantic('.', std::bind(&FishStrategy::instructionJump, this));
	// Arithmetic
	r.pushSemantic('+', std::bind(&FishStrategy::instructionAdd, this));
	r.pushSemantic('-', std::bind(&FishStrategy::instructionSub, this));
	r.pushSemantic('*', std::bind(&FishStrategy::instructionMult, this));
	r.pushSemantic(',', std::bind(&FishStrategy::instructionDiv, this));
	r.pushSemantic('%', std::bind(&FishStrategy::instructionModu, this));
	// Comparisons
	r.pushSemantic('=', std::bind(&FishStrategy::instructionEqual, this));
	r.pushSemantic(')', std::bind(&FishStrategy::instructionGreater, this));
	r.pushSemantic('(', std::bind(&FishStrategy::instructionLess, this));
	// Strings
	r.pushSemantic('\'', std::bind(&FishStrategy::instructionString, this, '\''));
	r.pushSemantic('\"', std::bind(&FishStrategy::instructionString, this, '\"'));
	// Stack Manipulation
	r.pushSemantic(':', std::bind(&FishStrategy::instructionDuplicate, this));
	r.pushSemantic('~', std::bind(&FishStrategy::instructionRemove, this));
	r.pushSemantic('$', std::bind(&FishStrategy::instructionSwap2, this));
	r.pushSemantic('@', std::bind(&FishStrategy::instructionSwap3, this));
	r.pushSemantic('l', std::bind(&FishStrategy::instructionLength, this));
	r.pushSemantic('{', std::bind(&FishStrategy::instructionShiftLeft, this));
	r.pushSemantic('}', std::bind(&FishStrategy::instructionShiftRight, this));
	r.pushSemantic('r', std::bind(&FishStrategy::instructionReverse, this));
	r.pushSemantic('[', std::bind(&FishStrategy::instructionCreateStack, this));
	r.pushSemantic(']', std::bind(&FishStrategy::instructionRemoveStack, this));
	// I/O
	r.pushSemantic('o', std::bind(&FishStrategy::instructionOutChar, this));
	r.pushSemantic('n', std::bind(&FishStrategy::instructionOutInt, this));
	r.pushSemantic('i', std::bind(&FishStrategy::instructionIn, this));
	// Miscellaneous
	r.pushSemantic('&', std::bind(&FishStrategy::instructionRegister, this));
	r.pushSemantic('g', std::bind(&FishStrategy::instructionGet, this));
	r.pushSemantic('p', std::bind(&FishStrategy::instructionPut, this));
	r.pushSemantic(';', std::bind(&FishStrategy::instructionEnd, this));

	r.setErrorHandler(std::bind(&FishStrategy::errorHandler, this, std::placeholders::_1));

	regs.push({false, 0});

}

FungeError FishStrategy::instructionSkip(){
	return ERROR_SKIP;
}

FungeError FishStrategy::instructionPush(stack_t n){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	stack.top().push(n);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionRight(){
	ip.setDelta(Vector{1, 0});
	return ERROR_NONE;
}

FungeError FishStrategy::instructionLeft(){
	ip.setDelta(Vector{-1, 0});
	return ERROR_NONE;
}

FungeError FishStrategy::instructionDown(){
	ip.setDelta(Vector{0, 1});
	return ERROR_NONE;
}

FungeError FishStrategy::instructionUp(){
	ip.setDelta(Vector{0, -1});
	return ERROR_NONE;
}

FungeError FishStrategy::instructionMirror1(){
	ip.setDelta(Vector{ip.getDelta().get(1), ip.getDelta().get(0)});
	return ERROR_NONE;
}

FungeError FishStrategy::instructionMirror2(){
	ip.setDelta(Vector{-ip.getDelta().get(1), -ip.getDelta().get(0)});
	return ERROR_NONE;
}

FungeError FishStrategy::instructionMirrorVert(){
	ip.setDelta(Vector{-ip.getDelta().get(0), ip.getDelta().get(1)});
	return ERROR_NONE;
}

FungeError FishStrategy::instructionMirrorHori(){
	ip.setDelta(Vector{ip.getDelta().get(0), -ip.getDelta().get(1)});
	return ERROR_NONE;
}

FungeError FishStrategy::instructionMirrorAll(){
	ip.setDelta(Vector{-ip.getDelta().get(0), -ip.getDelta().get(1)});
	return ERROR_NONE;
}

FungeError FishStrategy::instructionRandom(){
	size_t d = runner.getUniverse().dimensions()*2;
	int r = random(0, d-1);
	Vector v;
	if(r & 1){
		v.set(r>>1, -1);
	}else{
		v.set(r>>1, 1);
	}
	ip.setDelta(v);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionTrampoline(){
	ip.next();
	return ERROR_NONE;
}

FungeError FishStrategy::instructionConditional(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 1){
		if(!stack.top().pop()){
			ip.next();
		}
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionJump(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 2){
		stack_t y = stack.top().pop();
		stack_t x = stack.top().pop();
		ip.setPos(Vector{x,y} - ip.getDelta());
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionAdd(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 2){
		stack_t x = stack.top().pop();
		stack_t y = stack.top().pop();
		stack.top().push(y + x);
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionSub(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 2){
		stack_t x = stack.top().pop();
		stack_t y = stack.top().pop();
		stack.top().push(y - x);
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionMult(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 2){
		stack_t x = stack.top().pop();
		stack_t y = stack.top().pop();
		stack.top().push(y * x);
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionDiv(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 2){
		stack_t x = stack.top().pop();
		stack_t y = stack.top().pop();
		if(x == 0){
			return ERROR_UNSPEC;
		}
		stack.top().push(y / x);
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionModu(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 2){
		stack_t x = stack.top().pop();
		stack_t y = stack.top().pop();
		if(x == 0){
			return ERROR_UNSPEC;
		}
		stack.top().push(y % x);
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionEqual(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 2){
		stack_t x = stack.top().pop();
		stack_t y = stack.top().pop();
		stack.top().push(y == x);
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionGreater(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 2){
		stack_t x = stack.top().pop();
		stack_t y = stack.top().pop();
		stack.top().push(y > x);
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionLess(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 2){
		stack_t x = stack.top().pop();
		stack_t y = stack.top().pop();
		stack.top().push(y < x);
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionString(inst_t i){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	runner.setState(runner.getStringState(i));
	return ERROR_NONE;
}

FungeError FishStrategy::instructionDuplicate(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 1){
		stack_t x = stack.top().pop();
		stack.top().push(x);
		stack.top().push(x);
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionRemove(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 1){
		stack.top().pop();
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionSwap2(){
	if(stack.top().size() >= 2){
		stack_t x = stack.top().pop();
		stack_t y = stack.top().pop();
		stack.top().push(x);
		stack.top().push(y);
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionSwap3(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 3){
		stack_t x = stack.top().pop();
		stack_t y = stack.top().pop();
		stack_t z = stack.top().pop();
		stack.top().push(x);
		stack.top().push(z);
		stack.top().push(y);
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionLength(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	stack.top().push(stack.top().size());
	return ERROR_NONE;
}

FungeError FishStrategy::instructionShiftLeft(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	stack_t len = stack.top().size();
	stack_t temp[len];
	for(stack_t i = 0; i < len; ++i){
		temp[i] = stack.top().pop();
	}
	for(stack_t i = len-1; i > 0; --i){
		stack.top().push(temp[i-1]);
	}
	stack.top().push(temp[len-1]);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionShiftRight(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	stack_t len = stack.top().size();
	stack_t temp[len];
	for(stack_t i = 0; i < len; ++i){
		temp[i] = stack.top().pop();
	}
	stack.top().push(temp[0]);
	for(stack_t i = len-1; i > 0; --i){
		stack.top().push(temp[i]);
	}
	return ERROR_NONE;
}

FungeError FishStrategy::instructionReverse(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	stack_t len = stack.top().size();
	stack_t temp[len];
	for(stack_t i = 0; i < len; ++i){
		temp[i] = stack.top().pop();
	}
	for(stack_t i = 0; i < len; ++i){
		stack.top().push(temp[i]);
	}
	return ERROR_NONE;
}

FungeError FishStrategy::instructionCreateStack(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	stack_t x = stack.top().pop();
	stack.push();
	for(stack_t i = 0; i < x; ++i){
		stack.top().push(stack.second().pop());
	}
	regs.push({false, 0});
	return ERROR_NONE;
}

FungeError FishStrategy::instructionRemoveStack(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	while(stack.top().size() > 0){
		stack.second().push(stack.top().pop());
	}
	stack.pop();
	regs.pop();
	return ERROR_NONE;
}

FungeError FishStrategy::instructionOutChar(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 1){
		stack_t x = stack.top().pop();
		std::cout << static_cast<char>(x);
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionOutInt(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 1){
		stack_t x = stack.top().pop();
		std::cout << x;
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionIn(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	termios oldt;
	tcgetattr(STDIN_FILENO, &oldt);
	termios newt = oldt;
	newt.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	int q = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	if(q == EOF){
		q = -1;
	}
	stack.top().push(q);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionGet(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 3){
		const Vector& storage = ip.getStorage();
		Vector v = popVector(runner);
		stack.top().push(static_cast<stack_t>(field.get(v+storage)));
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionPut(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	if(stack.top().size() >= 3){
		const Vector& storage = ip.getStorage();
		Vector v = popVector(runner);
		field.set(v+storage, stack.top().pop());
		return ERROR_NONE;
	}else{
		return ERROR_UNSPEC;
	}
}

FungeError FishStrategy::instructionEnd(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	ip.stop();
	return ERROR_NONE;
}

FungeError FishStrategy::instructionRegister(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	reg& top = regs.top();

	FungeError ret = ERROR_UNSPEC;
	if(top.set){
		top.value = 0;
		top.set = false;
		ret = ERROR_NONE;
	}else{
		if(stack.size() >= 1){
			top.value = stack.top().pop();
			top.set = true;
			ret = ERROR_NONE;
		}
	}

	return ret;
}

FungeError FishStrategy::errorHandler(FungeError e){
	switch(e){
		[[unlikely]] case ERROR_NONE:
		[[unlikely]] case ERROR_SKIP:
		[[unlikely]] case ERROR_BLOCK:
			break;
		case ERROR_UNIMP:
			if(runner.isMode(FUNGE_MODE_DIVE)){
				return ERROR_NONE;
			}
			[[fallthrough]];
		case ERROR_NOTAVAIL:
		case ERROR_UNSPEC:
		[[unlikely]] default:
			std::cerr << "something smells fishy..." << std::endl;
			runner.getUniverse().killAll(1);
			// Unreachable
			break;
	}
	return e;
}

FungeStrategy* FishStrategy::clone(FungeRunner& r) const{
	return new FishStrategy(r);
}

} // namespace Funge
