#ifndef __FIGHTPROCESS_HPP__
#define __FIGHTPROCESS_HPP__

#include "GameProcess.hpp"
#include "Game.h"

class FightProcess : public GameProcess {

private:
	bool isFighting;
	int winner;
public:
	FightProcess(DisplayManager *dm, Map *m1, Map *m2, bool p, Rect ws) : GameProcess(dm, m1, m2, p, ws) {}
	~FightProcess() {}

	void init() {
		isFighting = true;
		winner = 0;
		erase();
		printMaps();
		refresh();
	}

	bool run() {
		while (isFighting) {
			// Get inputs
			int input = getch();
			bool isPlaying = manageInputs(input);
			if (!isPlaying) return (false);
			printGame();
		}
		return (true);
	}

	void end() {
		getch();
	}

private:

	void printGame() {
		if (playing) {
			std::string str;
			if (winner == 0) {
				// Print the game
				printMaps();
				str = "Player " + to_string(turn) + " turn.";
			} else {
				erase();
				str = "Player " + to_string(winner) + " wins !";
			}
			displayManager->printHere(winSize.x / 2, winSize.y - 1, str.c_str());
			refresh();
		}
	}

	bool manageInputs(int input) {
		switch (input) {
			case CTRLC: // Ctrl + c
			case ESCAPE: // Escape
				isFighting = false;
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
				int result;
				if (turn == TURN_P1) {
					result = map2->fire();
					if (result == END_OF_GAME) {
						isFighting = false;
						winner = 1;
					} else if (result != ACTION_FAIL) {
						if (result != ACTION_HIT) {
							switchPlayerTurn();
							map2->changeCursor(Rect(0, 0, 0, 0));
							map1->changeCursor(Rect(1, 1, 1, 1));
						}
					}
				} else if (turn == TURN_P2) {
					result = map1->fire();
					if (result == END_OF_GAME) {
						isFighting = false;
						winner = 2;
					}else if (result != ACTION_FAIL) {
						if (result != ACTION_HIT) {
							switchPlayerTurn();
							map2->changeCursor(Rect(1, 1, 1, 1));
							map1->changeCursor(Rect(0, 0, 0, 0));
						}
					}
				}
				break;
		}
		return true;
	}
	void handleArrows(int x, int y) {
		if (turn == TURN_P1)
			map2->changeCursorPos(x, y);
		if (turn == TURN_P2)
			map1->changeCursorPos(x, y);
	}

	void handleSpace() {
		if (turn == TURN_P1)
			map2->swapCursor();
		if (turn == TURN_P2)
			map1->swapCursor();
	}

	
};


#endif