/**
 * @file ScopedTermios.cpp
 * RAII object for termios.
 * @author Conlan Wesson
 */

#include "ScopedTermios.h"
#include <unistd.h>

ScopedTermios::ScopedTermios(tcflag_t cflag){
	tcgetattr(STDIN_FILENO, &oldt);
	termios newt = oldt;
	newt.c_lflag &= cflag;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

ScopedTermios::~ScopedTermios(){
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
