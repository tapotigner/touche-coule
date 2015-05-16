#ifndef __GAMEMANAGER_HPP__
#define __GAMEMANAGER_HPP__

#include <stdlib.h>
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

	static const int TURN_P1 = 1;
	static const int TURN_P2 = -1;
	static const int UP = 259;
	static const int DOWN = 258;
	static const int LEFT = 260;
	static const int RIGHT = 261;
	static const int ENTER = 10;
	static const int ESCAPE = 27;
	static const int SPACE = 32;
	static const int CTRLC = 3;

public:

	// Constructors
	GameManager(int x, int y) {
		displayManager = new DisplayManager();
		map1 = new Map(1);
		map2 = new Map(2);
		playing = true;
		winSizeX = x;
		winSizeY = y;
		turn = TURN_P1;
	}

	~GameManager() {

	}

	void run() {
		splashScreen();
		init();
		while (playing) {
			placeBoats();
			closeGame();
		}
	}

private:

	void placeBoats() {
		bool isPlacingBoat = true;
		int currentBoat = 0;
		if (turn == TURN_P1) {
			map1->changeCursor(Rect(1, 1, Map::BOATS_TEMPLATE[currentBoat], 1));
			map2->changeCursor(Rect(0, 0, 0, 0));
		}
		if (turn == TURN_P2) {
			map1->changeCursor(Rect(0, 0, 0, 0));
			map2->changeCursor(Rect(1, 1, Map::BOATS_TEMPLATE[currentBoat], 1));
		}
		init();
		while (isPlacingBoat) {
			// Get inputs
			int input = getch();
			// Manage inputs
			switch (input) {
				case CTRLC: // Ctrl + c
				case ESCAPE: // Escape
					closeGame();
					isPlacingBoat = false;
					break;
				case DOWN: // DOWN
					if (turn == TURN_P1)
						map1->changeCursorPos(0, 1);
					if (turn == TURN_P2)
						map2->changeCursorPos(0, 1);
					break;
				case UP: // UP
					if (turn == TURN_P1)
						map1->changeCursorPos(0, -1);
					if (turn == TURN_P2)
						map2->changeCursorPos(0, -1);
					break;
				case LEFT: // LEFT
					if (turn == TURN_P1)
						map1->changeCursorPos(-1, 0);
					if (turn == TURN_P2)
						map2->changeCursorPos(-1, 0);
					break;
				case RIGHT: // RIGHT
					if (turn == TURN_P1)
						map1->changeCursorPos(1, 0);
					if (turn == TURN_P2)
						map2->changeCursorPos(1, 0);
					break;
				case SPACE: // SPACE
					if (turn == TURN_P1)
						map1->swapCursor();
					if (turn == TURN_P2)
						map2->swapCursor();
					break;
				case ENTER: // ENTER
					if (turn == TURN_P1) {
						if (map1->addBoat()) {
							currentBoat++;
							map1->changeCursor(Rect(1, 1, Map::BOATS_TEMPLATE[currentBoat], 1));
						}
					} else if (turn == TURN_P2) {
						if (map2->addBoat()) {
							currentBoat++;
							map2->changeCursor(Rect(1, 1, Map::BOATS_TEMPLATE[currentBoat], 1));
						}
					}
					if (currentBoat == Map::NB_BOATS) {
						isPlacingBoat = false;
					}
					break;
			}
			if (playing) {
				// Print the game
				printMaps();
				std::string str = "Player " + to_string(turn) + ": place your boat. " + to_string(Map::BOATS_TEMPLATE[currentBoat]);
				displayManager->printHere(winSizeX / 2, winSizeY - 1, str.c_str());
				refresh();
			}
		}
		switchPlayerTurn();
		if (turn == TURN_P2)
			placeBoats();
	}

	void switchPlayerTurn() {
		turn *= -1;
	}

	void printMaps() {
		erase();
		map1->printMap(displayManager);
		map2->printMap(displayManager);
	}

	void splashScreen() {
		erase();
		std::string str = "Welcome to navy battle. Press a key to continue...";
		displayManager->printHere(winSizeX / 2, winSizeY / 2, str.c_str(), DisplayManager::RED);
		refresh();
		getch();
	}

	void init () {
		erase();
		printMaps();
		refresh();
	}

	void closeGame() {
		delete (map1);
		delete (map2);
		delete (displayManager);
		playing = false;
		exit(1);
	}
};

#endif