/**
 * @file ScopedTermios.h
 * RAII object for termios.
 * @author Conlan Wesson
 */

#pragma once

#include <termios.h>

class ScopedTermios {
	public:
		explicit ScopedTermios(tcflag_t cflag);
		~ScopedTermios();
	
	private:
		termios oldt;
};
