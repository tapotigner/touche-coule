#ifndef __PROCESS_HPP__
#define __PROCESS_HPP__

#include "DisplayManager.hpp"
#include "Map.hpp"
#include "Game.h"
#include "Rect.hpp"

class Process {

public:
	DisplayManager *displayManager;
	Rect winSize;

public:
	Process(DisplayManager *dm, Rect ws) {
		displayManager = dm;
		winSize = ws;
	}
	~Process() {}
	virtual void init() = 0;
	virtual bool run() = 0;
	virtual void end() = 0;

	
};


#endif