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
#include "FishUtil.h"
#include "ScopedTermios.h"

namespace Funge {

FishStrategy::FishStrategy(FungeRunner& r) :
	FungeStrategy(r),
	selected(0),
	file(nullptr),
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

	check_selected(selected);
	stack.at(selected).push(n);
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
	Vector v = ip.getDelta();
	dim_t y = v.get(1);
	v.set(1, v.get(0));
	v.set(0, y);
	ip.setDelta(v);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionMirror2(){
	Vector v = ip.getDelta();
	dim_t y = v.get(1);
	v.set(1, -v.get(0));
	v.set(0, -y);
	ip.setDelta(v);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionMirrorVert(){
	Vector v = ip.getDelta();
	v.set(0, -v.get(0));
	ip.setDelta(v);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionMirrorHori(){
	Vector v = ip.getDelta();
	v.set(1, -v.get(1));
	ip.setDelta(v);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionMirrorAll(){
	Vector v = ip.getDelta();
	v.set(0, -v.get(0));
	v.set(1, -v.get(1));
	ip.setDelta(v);
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

	check_stack(selected, 1);
	if(!stack.at(selected).pop()){
		ip.next();
	}
	return ERROR_NONE;
}

FungeError FishStrategy::instructionJump(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, runner.getUniverse().dimensions());
	Vector v = popVector(runner, &stack.at(selected));
	ip.setPos(v);
	return ERROR_NONE;	
}

FungeError FishStrategy::instructionAdd(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 2);
	stack_t x = stack.at(selected).pop();
	stack_t y = stack.at(selected).pop();
	stack.at(selected).push(y + x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionSub(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 2);
	stack_t x = stack.at(selected).pop();
	stack_t y = stack.at(selected).pop();
	stack.at(selected).push(y - x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionMult(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 2);
	stack_t x = stack.at(selected).pop();
	stack_t y = stack.at(selected).pop();
	stack.at(selected).push(y * x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionDiv(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 2);
	stack_t x = stack.at(selected).pop();
	stack_t y = stack.at(selected).pop();
	if(x == 0){
		return ERROR_UNSPEC;
	}
	stack.at(selected).push(y / x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionModu(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 2);
	stack_t x = stack.at(selected).pop();
	stack_t y = stack.at(selected).pop();
	if(x == 0){
		return ERROR_UNSPEC;
	}
	stack.at(selected).push(y % x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionEqual(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 2);
	stack_t x = stack.at(selected).pop();
	stack_t y = stack.at(selected).pop();
	stack.at(selected).push(y == x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionGreater(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 2);
	stack_t x = stack.at(selected).pop();
	stack_t y = stack.at(selected).pop();
	stack.at(selected).push(y > x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionLess(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 2);
	stack_t x = stack.at(selected).pop();
	stack_t y = stack.at(selected).pop();
	stack.at(selected).push(y < x);
	return ERROR_NONE;
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

	check_stack(selected, 1);
	stack_t x = stack.at(selected).pop();
	stack.at(selected).push(x);
	stack.at(selected).push(x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionRemove(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 1);
	stack.at(selected).pop();
	return ERROR_NONE;
}

FungeError FishStrategy::instructionSwap2(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 2);
	stack_t x = stack.at(selected).pop();
	stack_t y = stack.at(selected).pop();
	stack.at(selected).push(x);
	stack.at(selected).push(y);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionSwap3(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 3);
	stack_t x = stack.at(selected).pop();
	stack_t y = stack.at(selected).pop();
	stack_t z = stack.at(selected).pop();
	stack.at(selected).push(x);
	stack.at(selected).push(z);
	stack.at(selected).push(y);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionLength(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_selected(selected);
	stack.at(selected).push(stack.at(selected).size());
	return ERROR_NONE;
}

FungeError FishStrategy::instructionShiftLeft(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_selected(selected);
	stack_t len = stack.at(selected).size();
	stack_t temp[len];
	for(stack_t i = 0; i < len; ++i){
		temp[i] = stack.at(selected).pop();
	}
	for(stack_t i = len-1; i > 0; --i){
		stack.at(selected).push(temp[i-1]);
	}
	stack.at(selected).push(temp[len-1]);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionShiftRight(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_selected(selected);
	stack_t len = stack.at(selected).size();
	stack_t temp[len];
	for(stack_t i = 0; i < len; ++i){
		temp[i] = stack.at(selected).pop();
	}
	stack.at(selected).push(temp[0]);
	for(stack_t i = len-1; i > 0; --i){
		stack.at(selected).push(temp[i]);
	}
	return ERROR_NONE;
}

FungeError FishStrategy::instructionReverse(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_selected(selected);
	stack_t len = stack.at(selected).size();
	stack_t temp[len];
	for(stack_t i = 0; i < len; ++i){
		temp[i] = stack.at(selected).pop();
	}
	for(stack_t i = 0; i < len; ++i){
		stack.at(selected).push(temp[i]);
	}
	return ERROR_NONE;
}

FungeError FishStrategy::instructionCreateStack(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 1);
	size_t x = stack.at(selected).pop();

	stack.insert(selected);
	check_stack(selected+1, x);
	for(size_t i = 0; i < x; ++i){
		stack.at(selected).push(stack.at(selected+1).pop());
	}
	regs.push({false, 0});
	return ERROR_NONE;
}

FungeError FishStrategy::instructionRemoveStack(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_selected(selected);
	check_selected(selected+1);
	while(stack.at(selected).size() > 0){
		stack.at(selected+1).push(stack.at(selected).pop());
	}
	stack.pop();
	regs.pop();
	return ERROR_NONE;
}

FungeError FishStrategy::instructionOutChar(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 1);
	stack_t x = stack.at(selected).pop();
	std::cout << static_cast<char>(x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionOutInt(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 1);
	stack_t x = stack.at(selected).pop();
	std::cout << x;
	return ERROR_NONE;
}

FungeError FishStrategy::instructionIn(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	int q = EOF;
	if(file == nullptr){
		ScopedTermios term(~(ECHO | ICANON));
		q = getchar();
	}else{
		char i;
		*file >> i;
		q = i;
	}

	if(q == EOF){
		q = -1;
	}
	check_selected(selected);
	stack.at(selected).push(q);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionGet(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, runner.getUniverse().dimensions());
	const Vector& storage = ip.getStorage();
	Vector v = popVector(runner);
	stack.at(selected).push(static_cast<stack_t>(field.get(v+storage)));
	return ERROR_NONE;
}

FungeError FishStrategy::instructionPut(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, runner.getUniverse().dimensions()+1);
	const Vector& storage = ip.getStorage();
	Vector v = popVector(runner);
	field.set(v+storage, stack.at(selected).pop());
	return ERROR_NONE;
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
		check_stack(selected, 1);
		top.value = stack.at(selected).pop();
		top.set = true;
		ret = ERROR_NONE;
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
