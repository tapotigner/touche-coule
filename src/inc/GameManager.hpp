#ifndef __GAMEMANAGER_HPP__
#define __GAMEMANAGER_HPP__

#include <string>
#include "Utils.hpp"
#include "DisplayManager.hpp"
#include "Map.hpp"

class GameManager {
private:
	DisplayManager 	*displayManager;
	Map 			*map1;
	Map 			*map2;
	bool			playing;
	int 			winSizeX;
	int 			winSizeY;
	int 			turn;

public:

	// Constructors
	GameManager(int x, int y) {
		displayManager = new DisplayManager();
		map1 = new Map(0);
		map2 = new Map(1);
		playing = true;
		winSizeX = x;
		winSizeY = y;
		turn = 1;
	}

	~GameManager() {

	}

	void run() {
		map1->printMap(displayManager);
		map2->printMap(displayManager);
		std::string str = "Player's " + to_string(turn) + " turn.";
		displayManager->printHere(winSizeX - 1, winSizeY / 2, str.c_str());
	    while (playing) {
			refresh();
			int input = getch();
			if (input == 3 || input == 27) {
				closeGame();
			}
		}
	}

	void closeGame() {
		delete (map1);
		delete (map2);
		delete (displayManager);
		playing = false;
	}
};

#endif