/**
 * @file Funge.c
 * Main class for a full functional Befunge-98 interperter.
 * @author Conlan Wesson
 */

#include <fstream>
#include <iostream>
#include "Field.h"
#include "FungeConfig.h"
#include "FungeRunner.h"
#include "FungeManager.h"
#include "Vector.h"
#include <cstring>

int main(int argc, char **argv){
	const char* filepath = NULL;
	int a = 1;
	for( ; a < argc; ++a){
		if(argv[a][0] != '-'){
			break;
		}else if(strncmp(argv[a], "-std=", 5) == 0){
			strtok(argv[a], "=");
			char* arg = strtok(NULL, "=");
			if(strcmp(arg, "une93") == 0){
				Funge::funge_config.dimensions = 1;
				Funge::funge_config.standard = 93;
			}else if(strcmp(arg, "une98") == 0){
				Funge::funge_config.dimensions = 1;
				Funge::funge_config.standard = 98;
			}else if(strcmp(arg, "be93") == 0){
				Funge::funge_config.dimensions = 2;
				Funge::funge_config.standard = 93;
			}else if(strcmp(arg, "be98") == 0){
				Funge::funge_config.dimensions = 2;
				Funge::funge_config.standard = 98;
			}else if(strcmp(arg, "tre98") == 0){
				Funge::funge_config.dimensions = 3;
				Funge::funge_config.standard = 98;
			}else{
				std::cerr << "Unsupported standard: " << arg << std::endl;
				return EINVAL;
			}
		}else if(strncmp(argv[a], "-fno-concurrent", 15) == 0){
			Funge::funge_config.concurrent = false;
		}else if(strncmp(argv[a], "-fno-filesystem", 15) == 0){
			Funge::funge_config.filesystem = false;
		}
	}
	if(a < argc){
		filepath = argv[a];
	}
	if(!filepath){
		std::cerr << "No input file specified.";
		return EINVAL;
	}
	
	std::ifstream file(filepath);
	Funge::Field field(file, Funge::funge_config.dimensions);
	Funge::FungeRunner runner(field);
	
	Funge::FungeManager::getInstance()->waitAll();
	
	return 0;
}
