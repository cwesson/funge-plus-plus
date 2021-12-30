/**
 * @file Funge.c
 * Main class for a full functional Befunge-98 interperter.
 * @author Conlan Wesson
 */

#include "Field.h"
#include "FungeConfig.h"
#include "FungeRunner.h"
#include "FungeMultiverse.h"
#include "Vector.h"
#include <cstring>
#include <fstream>
#include <future>
#include <iostream>

int main(int argc, char **argv, char **envp){
	Funge::FungeConfig funge_config;
	std::string filepath;
	int a = 1;
	for( ; a < argc; ++a){
		if(argv[a][0] != '-'){
			break;
		}else if(strncmp(argv[a], "-std=", 5) == 0){
			std::strtok(argv[a], "=");
			char* arg = std::strtok(NULL, "=");
			if(strcmp(arg, "une93") == 0){
				funge_config.dimensions = 1;
				funge_config.standard = 93;
			}else if(strcmp(arg, "une98") == 0){
				funge_config.dimensions = 1;
				funge_config.standard = 98;
			}else if(strcmp(arg, "be93") == 0){
				funge_config.dimensions = 2;
				funge_config.standard = 93;
			}else if(strcmp(arg, "be98") == 0){
				funge_config.dimensions = 2;
				funge_config.standard = 98;
			}else if(strcmp(arg, "tre98") == 0){
				funge_config.dimensions = 3;
				funge_config.standard = 98;
			}else{
				std::cerr << "Unsupported standard: " << arg << std::endl;
				return EINVAL;
			}
			if(funge_config.standard == 93){
				funge_config.topo = Funge::TOPO_TORUS;
				funge_config.strings = Funge::STRING_MULTISPACE;
				funge_config.cells = Funge::CELL_CHAR;
			}else{
				funge_config.topo = Funge::TOPO_LAHEY;
				funge_config.strings = Funge::STRING_SGML;
				funge_config.cells = Funge::CELL_INT;
			}
		}else if(strcmp(argv[a], "-fconcurrent") == 0){
			funge_config.concurrent = true;
		}else if(strcmp(argv[a], "-fexecute") == 0){
			funge_config.execute = true;
		}else if(strcmp(argv[a], "-ffilesystem") == 0){
			funge_config.filesystem = true;
		}else if(strcmp(argv[a], "-fno-concurrent") == 0){
			funge_config.concurrent = false;
		}else if(strcmp(argv[a], "-fno-execute") == 0){
			funge_config.execute = false;
		}else if(strcmp(argv[a], "-fno-filesystem") == 0){
			funge_config.filesystem = false;
		}else if(strcmp(argv[a], "-finvert-hl") == 0){
			funge_config.inverthl = true;
		}else if(strncmp(argv[a], "-ftopo=", 7) == 0){
			std::strtok(argv[a], "=");
			char* arg = strtok(NULL, "=");
			if(strcmp(arg, "torus") == 0){
				funge_config.topo = Funge::TOPO_TORUS;
			}else if(strcmp(arg, "lahey") == 0){
				funge_config.topo = Funge::TOPO_LAHEY;
			}else{
				std::cerr << "Unsupported topology: " << arg << std::endl;
				return EINVAL;
			}
		}else if(strncmp(argv[a], "-fstrings=", 10) == 0){
			std::strtok(argv[a], "=");
			char* arg = std::strtok(NULL, "=");
			if(strcmp(arg, "multispace") == 0){
				funge_config.strings = Funge::STRING_MULTISPACE;
			}else if(strcmp(arg, "sgml") == 0){
				funge_config.strings = Funge::STRING_SGML;
			}else if(strcmp(arg, "c") == 0){
				funge_config.strings = Funge::STRING_C;
			}else{
				std::cerr << "Unsupported strings: " << arg << std::endl;
				return EINVAL;
			}
		}else if(strncmp(argv[a], "-fcells=", 8) == 0){
			std::strtok(argv[a], "=");
			char* arg = std::strtok(NULL, "=");
			if(strcmp(arg, "char") == 0){
				funge_config.cells = Funge::CELL_CHAR;
			}else if(strcmp(arg, "int") == 0){
				funge_config.cells = Funge::CELL_INT;
			}else{
				std::cerr << "Unsupported cell size: " << arg << std::endl;
				return EINVAL;
			}
		}else if(strncmp(argv[a], "-fthreads=", 10) == 0){
			std::strtok(argv[a], "=");
			char* arg = std::strtok(NULL, "=");
			if(strcmp(arg, "native") == 0){
				funge_config.threads = Funge::THREAD_NATIVE;
			}else if(strcmp(arg, "funge") == 0){
				funge_config.threads = Funge::THREAD_FUNGE;
			}else{
				std::cerr << "Unsupported threading: " << arg << std::endl;
				return EINVAL;
			}
		}else if(strncmp(argv[a], "-l", 2) == 0){
			std::string fing(&argv[a][2]);
			uint64_t fingerprint = std::accumulate(fing.begin(), fing.end(), 0, [](uint64_t f, char c){return (f << 8) + c;});
			funge_config.fingerprints.push_back(fingerprint);
		}else if(strcmp(argv[a], "-g") == 0){
			funge_config.mode |= Funge::FUNGE_MODE_DEBUG;
		}
	}
	if(a < argc){
		filepath = argv[a++];
		funge_config.args.push_back(filepath);
	}
	if(filepath == ""){
		std::cerr << "No input file specified.";
		return EINVAL;
	}
	for( ; a < argc; ++a){
		funge_config.args.push_back(std::string(argv[a]));
	}
	for(char **env = envp; *env != nullptr; ++env)
	{
		funge_config.env.push_back(std::string(*env));
	}
	
	std::ifstream file(filepath);
	if(file.fail()){
		return EIO;
	}
	Funge::Field::FileFormat fmt = Funge::Field::FORMAT_BF;
	std::string ext = filepath.substr(filepath.find_last_of(".") + 1);
	if(ext == "beq"){
		fmt = Funge::Field::FORMAT_BEQ;
		funge_config.fingerprints.push_back(0x4e46554e);
	}else if(ext == "fl"){
		fmt = Funge::Field::FORMAT_FL;
	}
	funge_config.name = basename(filepath.c_str());
	
	Funge::FungeUniverse* universe = Funge::FungeMultiverse::getInstance().create(file, fmt, &funge_config);
	universe->createRunner(Funge::Vector{0}, Funge::Vector{1});
	auto ret = std::async(std::launch::async, &Funge::FungeUniverse::waitAll, universe);
	ret.wait();
	return ret.get();
}
