/**
 * @file StarfishStrategy.cpp
 * Strategy for *><> commands.
 * @author Conlan Wesson
 */

#include "StarfishStrategy.h"
#include "FungeRunner.h"
#include "FungeUniverse.h"
#include "FungeUtilities.h"
#include "FishUtil.h"
#include <algorithm>

namespace Funge {

StarfishStrategy::StarfishStrategy(FungeRunner& r) :
	FishStrategy(r),
	fisherstate(FISHER_UP),
	fishercache({1, 0})
{
	// Movement
	r.pushSemantic('`', std::bind(&StarfishStrategy::instructionFisherman, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('C', std::bind(&StarfishStrategy::instructionCall, this));
	r.pushSemantic('R', std::bind(&StarfishStrategy::instructionReturn, this));
	r.pushSemantic('u', std::bind(&StarfishStrategy::instructionDive, this), FungeSemantic::MOVEMENT);
	r.pushSemantic('O', std::bind(&StarfishStrategy::instructionRise, this), FungeSemantic::MOVEMENT);
	// Stack Manipulation
	r.pushSemantic('I', std::bind(&StarfishStrategy::instructionIncrement, this));
	r.pushSemantic('D', std::bind(&StarfishStrategy::instructionDecrement, this));
	// I/O
	r.pushSemantic('F', std::bind(&StarfishStrategy::instructionFile, this));
	// Miscellaneous
	r.pushSemantic('S', std::bind(&StarfishStrategy::instructionSleep, this));
	r.pushSemantic('h', std::bind(&StarfishStrategy::instructionHour, this));
	r.pushSemantic('m', std::bind(&StarfishStrategy::instructionMinute, this));
	r.pushSemantic('s', std::bind(&StarfishStrategy::instructionSecond, this));

	ip.addObserver(std::bind(&StarfishStrategy::fishermanChange, this, std::placeholders::_1));
}

FungeError StarfishStrategy::instructionFisherman(){
	if(ip.getDelta().get(1) == 0){
		if(fisherstate == FISHER_UP){
			ip.setDelta(Vector{0, 1});
			fisherstate = FISHER_DOWN;
		}else{
			ip.setDelta(Vector{0, -1});
			fisherstate = FISHER_UP;
		}
	}else{
		ip.setDelta(fishercache);
	}
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionCall(){
	stack.insert(selected+1);
	pushVector(SECOND, ip.getPos());

	check_stack(top, runner.getUniverse().dimensions());
	Vector v = popVector(TOP);
	ip.setPos(v);
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionReturn(){
	check_stack(second, runner.getUniverse().dimensions());
	Vector v = popVector(SECOND);
	ip.setPos(v);
	stack.remove(selected+1);
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionDive(){
	runner.getUniverse().setMode(FUNGE_MODE_DIVE);
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionRise(){
	runner.getUniverse().clearMode(FUNGE_MODE_DIVE);
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionIncrement(){
	return stack.increment();
}

FungeError StarfishStrategy::instructionDecrement(){
	return stack.decrement();
}

FungeError StarfishStrategy::instructionFile(){
	FungeError ret = ERROR_UNSPEC;
	if(runner.getUniverse().allowFilesystem()){
		check_stack(top, 1);
		size_t x = pop(TOP);
		check_stack(top, x);
		if(file == nullptr){
			std::string str;
			for (size_t i = 0; i < x; ++i){
				str += pop(TOP);
			}
			std::reverse(str.begin(), str.end());
			file = new std::ifstream(str);
			filepath = str;
		}else{
			file->close();
			delete file;
			file = nullptr;

			std::ofstream ofile(filepath);
			for (size_t i = 0; i < x; ++i){
				ofile << static_cast<char>(pop(TOP));
			}
		}
		ret = ERROR_NONE;
	}else{
		std::cerr << "Run with -ffilesystem to enable execution." << std::endl;
		ret = ERROR_NOTAVAIL;
	}
	return ret;
}

FungeError StarfishStrategy::instructionSleep(){
	check_stack(top, 1);
	double ms = pop(TOP) * 100.0;
	std::this_thread::sleep_for(std::chrono::microseconds(static_cast<unsigned int>(1000*ms)));
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionHour(){
	std::time_t now = std::time(nullptr);
	std::tm* dt = std::localtime(&now);

	check_selected(selected);
	push(TOP, dt->tm_hour);
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionMinute(){
	std::time_t now = std::time(nullptr);
	std::tm* dt = std::localtime(&now);

	check_selected(selected);
	push(TOP, dt->tm_min);
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionSecond(){
	std::time_t now = std::time(nullptr);
	std::tm* dt = std::localtime(&now);

	check_selected(selected);
	push(TOP, dt->tm_sec);
	return ERROR_NONE;
}

void StarfishStrategy::fishermanChange(const Vector& delta){
	if(delta.get(0) != 0 && delta.get(1) == 0){
		fishercache = delta;
	}
}

}; // namespace Funge
