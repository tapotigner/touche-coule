#ifndef __GAMEPROCESS_HPP__
#define __GAMEPROCESS_HPP__

#include "Process.hpp"

class GameProcess : public Process {
public:
	int turn;
	Map *map1;
	Map *map2;
	bool playing;

	GameProcess(DisplayManager *dm, Map *m1, Map *m2, bool p, Rect ws) : Process(dm, ws) {
		map1 = m1;
		map2 = m2;
		playing = p;
		turn = TURN_P1;
	}

	~GameProcess() {}
	virtual void init() = 0;
	virtual bool run() = 0;
	virtual void end() = 0;
	
	void switchPlayerTurn() {
		turn *= -1;
		erase();
		std::string str = "Player " + to_string(turn);
		displayManager->printHere(winSize.x / 2, winSize.y / 2, str.c_str());
		std::string str2 = "Press a key to continue.";
		displayManager->printHere(winSize.x / 2, winSize.y / 2 + 1, str2.c_str());
		getch();
	}

	void printMaps() {
		erase();
		map1->printMap(displayManager, turn);
		map2->printMap(displayManager, turn);
	}
};

#endif