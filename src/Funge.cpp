/**
 * @file Funge.c
 * Main class for a full functional Befunge-98 interperter.
 * @author Conlan Wesson
 */

#include <fstream>
#include <iostream>
#include "Field.h"
#include "FungeRunner.h"
#include "FungeManager.h"
#include "Vector.h"

int main(int argc, char **argv){
	const char* filepath = NULL;
	if(argc > 1){
		filepath = argv[1];
	}
	if(!filepath){
		std::cerr << "No input file specified.";
		return 1;
	}
	
	std::ifstream file(filepath);
	Funge::Field field(file);
	Funge::FungeRunner runner(field);
	
	Funge::FungeManager::getInstance()->waitAll();
	
	return 0;
}
