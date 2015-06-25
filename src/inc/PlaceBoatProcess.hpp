#ifndef __PLACEBOATPROCESS_HPP__
#define __PLACEBOATPROCESS_HPP__

#include "GameProcess.hpp"

class PlaceBoatProcess : public GameProcess {

private:
	bool isPlacingBoat;
	int currentBoat;

public:
	PlaceBoatProcess(DisplayManager *dm, Map *m1, Map *m2, bool p, Rect ws, bool mt) : GameProcess(dm, m1, m2, p, ws, mt) {
		turn = turn;
	}
	~PlaceBoatProcess() {}

	void init() {
		isPlacingBoat = true;
		currentBoat = 0;
		message = "Player " + to_string(turn) + ": place your boat. ";
		if (turn == TURN_P1) {
			map1->changeCursor(Rect(1, 1, BOATS_TEMPLATE[currentBoat], 1));
			map2->changeCursor(Rect(0, 0, 0, 0));
		}
		if (turn == TURN_P2) {
			map1->changeCursor(Rect(0, 0, 0, 0));
			map2->changeCursor(Rect(1, 1, BOATS_TEMPLATE[currentBoat], 1));
		}
		printGame();
		refresh();
	}
/*
	bool run() {
		if (turn == TURN_P1) {
			map1->changeCursor(Rect(1, 1, BOATS_TEMPLATE[currentBoat], 1));
			map2->changeCursor(Rect(0, 0, 0, 0));
		}
		if (turn == TURN_P2) {
			map1->changeCursor(Rect(0, 0, 0, 0));
			map2->changeCursor(Rect(1, 1, BOATS_TEMPLATE[currentBoat], 1));
		}
		while (isPlacingBoat) {
			int input = getch();
			bool isExiting = manageInput(input);
			if (!isExiting) return false;
			message = "Player " + to_string(turn) + ": place your boat. ";
			printGame();
		}
		switchPlayerTurn();
		if (turn == TURN_P2) {
			init();
			if (run()) {
				return (true);
			} else {
				return (false);
			}
		}
	}
*/

	void end() {
		
	}

private:

	void printGame() {
		if (playing) {
			printMaps();
			printMessage();
			refresh();
		}
	}
/*
	bool manageInput(int input) {
		switch (input) {
			case CTRLC: // Ctrl + c
			case ESCAPE: // Escape
				isPlacingBoat = false;
				return false;
			case DOWN: // DOWN
				handleArrows(0, 1);
				break;
			case UP: // UP
				handleArrows(0, -1);
				break;
			case LEFT: // LEFT
				handleArrows(-1, 0);
				break;
			case RIGHT: // RIGHT
				handleArrows(1, 0);
				break;
			case SPACE: // SPACE
				handleSpace();
				break;
			case ENTER: // ENTER
				handleEnter();
				break;
		}
		return true;
	}
*/
	void handleArrows(int x, int y) {
		if (turn == TURN_P1)
			map1->changeCursorPos(x, y);
		if (turn == TURN_P2)
			map2->changeCursorPos(x, y);
	}

	void handleSpace() {
		if (turn == TURN_P1)
			map1->swapCursor();
		if (turn == TURN_P2)
			map2->swapCursor();
	}

	void handleEnter() {
		if (turn == TURN_P1) {
			if (map1->addBoat(displayManager, currentBoat * turn)) {
				currentBoat++;
				map1->changeCursor(Rect(1, 1, BOATS_TEMPLATE[currentBoat], 1));
			}
		} else if (turn == TURN_P2) {
			if (map2->addBoat(displayManager, currentBoat * turn)) {
				currentBoat++;
				map2->changeCursor(Rect(1, 1, BOATS_TEMPLATE[currentBoat], 1));
			}
		}
		if (currentBoat == NB_BOATS) {
			isPlacingBoat = false;
			map1->changeCursor(Rect(0, 0, 0, 0));
			map2->changeCursor(Rect(1, 1, 1, 1));
		}
	}
};

#endif