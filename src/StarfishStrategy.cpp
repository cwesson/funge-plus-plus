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
	r.pushSemantic('`', std::bind(&StarfishStrategy::instructionFisherman, this));
	r.pushSemantic('C', std::bind(&StarfishStrategy::instructionCall, this));
	r.pushSemantic('R', std::bind(&StarfishStrategy::instructionReturn, this));
	r.pushSemantic('u', std::bind(&StarfishStrategy::instructionDive, this));
	r.pushSemantic('O', std::bind(&StarfishStrategy::instructionRise, this));
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
}

FungeError StarfishStrategy::instructionFisherman(){
	if(ip.getDelta().get(1) == 0){
		fishercache = ip.getDelta();
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
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	stack.insert(selected+1);
	pushVector(runner, ip.getPos(), &stack.at(selected+1));

	check_stack(selected, runner.getUniverse().dimensions());
	Vector v = popVector(runner, &stack.at(selected));
	ip.setPos(v);
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionReturn(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected+1, runner.getUniverse().dimensions());
	Vector v = popVector(runner, &stack.at(selected+1));
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
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	--selected;
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionDecrement(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	++selected;
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionFile(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	FungeError ret = ERROR_UNSPEC;
	if(runner.getUniverse().allowFilesystem()){
		check_stack(selected, 1);
		size_t x = stack.at(selected).pop();
		check_stack(selected, x);
		if(file == nullptr){
			std::string str;
			for (size_t i = 0; i < x; ++i){
				str += stack.at(selected).pop();
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
				ofile << static_cast<char>(stack.at(selected).pop());
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
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	check_stack(selected, 1);
	stack_t s = stack.at(selected).pop();
	std::this_thread::sleep_for(std::chrono::milliseconds(100*s));
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionHour(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	std::time_t now = std::time(nullptr);
	std::tm* dt = std::localtime(&now);

	check_selected(selected);
	stack.at(selected).push(dt->tm_hour);
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionMinute(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	std::time_t now = std::time(nullptr);
	std::tm* dt = std::localtime(&now);

	check_selected(selected);
	stack.at(selected).push(dt->tm_min);
	return ERROR_NONE;
}

FungeError StarfishStrategy::instructionSecond(){
	if(runner.isMode(FUNGE_MODE_DIVE)){
		return ERROR_NONE;
	}

	std::time_t now = std::time(nullptr);
	std::tm* dt = std::localtime(&now);

	check_selected(selected);
	stack.at(selected).push(dt->tm_sec);
	return ERROR_NONE;
}

}; // namespace Funge
