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

	enum Inputs {
		INIT = 0,
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	};

	// Constructors
	GameManager(int x, int y) {
		displayManager = new DisplayManager();
		map1 = new Map(1);
		map1->changeCursor(Rect(1, 1, 3, 1));
		map2 = new Map(2);
		playing = true;
		winSizeX = x;
		winSizeY = y;
		turn = 1;
	}

	~GameManager() {

	}

	/*
	 * 1. Display 2 maps and text "player1 turn"
	 * 2. Display player 1 first boat
	 * 3. Put all boats
	 * 4. Next player
	 * 5. ça commence !
	 */



	void run() {
		erase();
		std::string str = "Welcome to navy battle. Press a key to continue...";
		displayManager->printHere(winSizeX / 2, winSizeY / 2, str.c_str(), DisplayManager::RED);
		refresh();
		while (playing) {
			// Get inputs
			int input = getch();
			// Manage inputs
			if (input == 3 || input == 27) { // Escape or Ctrl+C
				closeGame();
				break;
			} else if (input == 258) { // DOWN
				if (turn == 1) {
					map1->changeCursorPos(0, 1);
				}
			} else if (input == 259) { // UP
				if (turn == 1) {
					map1->changeCursorPos(0, -1);
				}
			} else if (input == 260) { // LEFT
				if (turn == 1) {
					map1->changeCursorPos(-1, 0);
				}
			} else if (input == 261) { //RIGHT
				if (turn == 1) {
					map1->changeCursorPos(1, 0);
				}
			} else if (input == 32) { // SPACE
				if (turn == 1) {
					map1->swapCursor();
				}
			}
			// Print the game
			erase();
			map1->printMap(displayManager);
			map2->printMap(displayManager);
			std::string str = "Player's " + to_string(turn) + " turn.";
			displayManager->printHere(winSizeX / 2, winSizeY - 1, str.c_str());
			refresh();
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