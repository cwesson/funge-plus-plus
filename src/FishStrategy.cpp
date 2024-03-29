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
	filepath(),
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
	r.pushSemantic('>', std::bind(&FishStrategy::instructionRight, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('<', std::bind(&FishStrategy::instructionLeft, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('v', std::bind(&FishStrategy::instructionDown, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('^', std::bind(&FishStrategy::instructionUp, this), FungeSemantic::MOVEMENT);
	// Mirrors
	r.pushSemantic('\\', std::bind(&FishStrategy::instructionMirror1, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('/', std::bind(&FishStrategy::instructionMirror2, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('|', std::bind(&FishStrategy::instructionMirrorVert, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('_', std::bind(&FishStrategy::instructionMirrorHori, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('#', std::bind(&FishStrategy::instructionMirrorAll, this), FungeSemantic::MOVEMENT);
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
	check_selected(selected);
	push(TOP, n);
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
	check_stack(top, 1);
	if(!pop(TOP)){
		ip.next();
	}
	return ERROR_NONE;
}

FungeError FishStrategy::instructionJump(){
	check_stack(top, runner.getUniverse().dimensions());
	Vector v = popVector(TOP);
	ip.setPos(v);
	return ERROR_NONE;	
}

FungeError FishStrategy::instructionAdd(){
	check_stack(top, 2);
	double x = pop(TOP);
	double y = pop(TOP);
	push(TOP, y + x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionSub(){
	check_stack(top, 2);
	double x = pop(TOP);
	double y = pop(TOP);
	push(TOP, y - x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionMult(){
	check_stack(top, 2);
	double x = pop(TOP);
	double y = pop(TOP);
	push(TOP, y * x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionDiv(){
	check_stack(top, 2);
	double x = pop(TOP);
	double y = pop(TOP);
	if(x == 0){
		return ERROR_UNSPEC;
	}
	push(TOP, y / x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionModu(){
	check_stack(top, 2);
	stack_t x = pop(TOP);
	stack_t y = pop(TOP);
	if(x == 0){
		return ERROR_UNSPEC;
	}
	push(TOP, y % x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionEqual(){
	check_stack(top, 2);
	double x = pop(TOP);
	double y = pop(TOP);
	push(TOP, y == x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionGreater(){
	check_stack(top, 2);
	double x = pop(TOP);
	double y = pop(TOP);
	push(TOP, y > x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionLess(){
	check_stack(top, 2);
	double x = pop(TOP);
	double y = pop(TOP);
	push(TOP, y < x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionString(inst_t i){
	runner.setState(runner.getStringState(i));
	return ERROR_NONE;
}

FungeError FishStrategy::instructionDuplicate(){
	check_stack(top, 1);
	double x = pop(TOP);
	push(TOP, x);
	push(TOP, x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionRemove(){
	check_stack(top, 1);
	pop(TOP);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionSwap2(){
	check_stack(top, 2);
	double x = pop(TOP);
	double y = pop(TOP);
	push(TOP, x);
	push(TOP, y);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionSwap3(){
	check_stack(top, 3);
	double x = pop(TOP);
	double y = pop(TOP);
	double z = pop(TOP);
	push(TOP, x);
	push(TOP, z);
	push(TOP, y);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionLength(){
	check_selected(selected);
	push(TOP, stack.top().size());
	return ERROR_NONE;
}

FungeError FishStrategy::instructionShiftLeft(){
	check_selected(selected);
	stack_t len = stack.top().size();
	double temp[len];
	for(stack_t i = 0; i < len; ++i){
		temp[i] = pop(TOP);
	}
	for(stack_t i = len-1; i > 0; --i){
		push(TOP, temp[i-1]);
	}
	push(TOP, temp[len-1]);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionShiftRight(){
	check_selected(selected);
	stack_t len = stack.top().size();
	double temp[len];
	for(stack_t i = 0; i < len; ++i){
		temp[i] = pop(TOP);
	}
	push(TOP, temp[0]);
	for(stack_t i = len-1; i > 0; --i){
		push(TOP, temp[i]);
	}
	return ERROR_NONE;
}

FungeError FishStrategy::instructionReverse(){
	check_selected(selected);
	stack_t len = stack.top().size();
	double temp[len];
	for(stack_t i = 0; i < len; ++i){
		temp[i] = pop(TOP);
	}
	for(stack_t i = 0; i < len; ++i){
		push(TOP, temp[i]);
	}
	return ERROR_NONE;
}

FungeError FishStrategy::instructionCreateStack(){
	check_stack(top, 1);
	size_t x = pop(TOP);

	stack.insert(selected);
	check_stack(second, x);
	for(size_t i = 0; i < x; ++i){
		push(TOP, pop(SECOND));
	}
	regs.push({false, 0});
	return ERROR_NONE;
}

FungeError FishStrategy::instructionRemoveStack(){
	check_selected(selected);
	check_selected(selected+1);
	while(stack.top().size() > 0){
		push(SECOND, pop(TOP));
	}
	stack.pop();
	regs.pop();
	return ERROR_NONE;
}

FungeError FishStrategy::instructionOutChar(){
	check_stack(top, 1);
	stack_t x = pop(TOP);
	std::cout << static_cast<char>(x);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionOutInt(){
	check_stack(top, 1);
	double x = pop(TOP);
	int64_t i = x;
	if(x == i){
		std::cout << i;
	}else{
		std::cout << x;
	}
	return ERROR_NONE;
}

FungeError FishStrategy::instructionIn(){
	int q = EOF;
	if(file == nullptr){
		ScopedTermios term(~(ECHO | ICANON));
		q = getchar();
	}else{
		q = file->get();
	}

	if(q == EOF){
		q = -1;
	}
	check_selected(selected);
	push(TOP, q);
	return ERROR_NONE;
}

FungeError FishStrategy::instructionGet(){
	check_stack(top, runner.getUniverse().dimensions());
	const Vector& storage = ip.getStorage();
	Vector v = popVector(TOP);
	push(TOP, static_cast<stack_t>(field.get(v+storage)));
	return ERROR_NONE;
}

FungeError FishStrategy::instructionPut(){
	check_stack(top, runner.getUniverse().dimensions()+1);
	const Vector& storage = ip.getStorage();
	Vector v = popVector(TOP);
	field.put(v+storage, pop(TOP));
	return ERROR_NONE;
}

FungeError FishStrategy::instructionEnd(){
	ip.stop();
	return ERROR_NONE;
}

FungeError FishStrategy::instructionRegister(){
	reg& top = regs.top();

	FungeError ret = ERROR_UNSPEC;
	if(top.set){
		top.value = 0;
		top.set = false;
		ret = ERROR_NONE;
	}else{
		check_stack(top, 1);
		top.value = pop(TOP);
		top.set = true;
		ret = ERROR_NONE;
	}

	return ret;
}

double FishStrategy::pop(StackIndex index){
	stack_t n;
	switch(index){
		default:
		case TOP:
			n = stack.top().pop();
			break;
		case SECOND:
			n = stack.second().pop();
			break;
	}
	return *reinterpret_cast<double*>(&n);
}

Vector FishStrategy::popVector(StackIndex index){
	Vector v;
	size_t d = runner.getUniverse().dimensions();
	for(size_t i = d; i > 0; --i){
		stack_t x = pop(index);
		v.set(i-1, x);
	}
	return v;
}

void FishStrategy::push(StackIndex index, double n){
	stack_t s = *reinterpret_cast<stack_t*>(&n);
	switch(index){
		default:
		case TOP:
			stack.top().push(s);
			break;
		case SECOND:
			stack.second().push(s);
			break;
	}
}

void FishStrategy::pushVector(StackIndex index, const Vector& v){
	size_t d = runner.getUniverse().dimensions();
	for(size_t i = 0; i < d; ++i){
		push(index, v.get(i));
	}
}

FungeError FishStrategy::push(stack_t n){
	push(TOP, n);
	return ERROR_NONE;
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
