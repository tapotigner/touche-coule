#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <vector>
#include "DisplayManager.hpp"
#include "Rect.hpp"
#include "Indicator.hpp"
#include "Boat.hpp"
#include "Game.h"

class Map {
private:
	int player;
	int xfrom;
	int yfrom;
	int map[64][64];
	std::vector<Boat *> boats;
	Rect cursor = Rect(0, 0, 0, 0);
	Indicator *indicator;

public:

	// Constructors
	Map(int p, DisplayManager *dm) {
		player = p;
		if (player == 1) {
			xfrom = 1;
			yfrom = 1;
		} else {
			xfrom = (MAP_SIZE + 1) * X_MODIFIER + (2 * X_MODIFIER);
			yfrom = 1;
		}
		init(dm);
	}

	~Map() {

	}

private:
	void init(DisplayManager *dm) {
		// initializing the map
		int x = 0;
		int y = 0;
		while (x < MAP_SIZE) {
			y = 0;
			while (y < MAP_SIZE) {
				map[x][y] = MAP_WATER;
				y++;
			}
			x++;
		}
		indicator = new Indicator(dm, xfrom, yfrom);
	}

	void printGrid(DisplayManager *dm) {
		int x = 0;
		int y = 0;
		while (x < (MAP_SIZE + 1) * X_MODIFIER + 1) {
			y = 0;
			while (y < (MAP_SIZE + 1) * Y_MODIFIER + 1) {
				if (x % X_MODIFIER == 0 || y % Y_MODIFIER == 0) {
					dm->printHere(x+xfrom, y+yfrom, ACS_CKBOARD, DisplayManager::GRID_COLOR);
				}
				y++;
			}
			x++;
		}
	}

	void printContent(DisplayManager *dm, int turn) {
		int x = 0;
		int y = 0;
		while (x < MAP_SIZE) {
			y = 0;
			while (y < MAP_SIZE) {
				if (map[x][y] == MAP_BOAT) {
				} else if (map[x][y] == MAP_DESTROYED) {
					printCase(dm, x, y, DisplayManager::DESTROYED_COLOR);
				} else if (map[x][y] == MAP_FIRED) {
					printCase(dm, x, y, DisplayManager::FIRED_COLOR);
				} else if (map[x][y] == MAP_WATER) {
					printCase(dm, x, y, DisplayManager::WATER_COLOR);
				}
				y++;
			}
			x++;
		}
	}

	void printCase(DisplayManager *dm, int x, int y, int color) {
		x = x * X_MODIFIER + xfrom + 2 + X_MODIFIER;
		y = y * Y_MODIFIER + yfrom + 2 + Y_MODIFIER;
		for (int i = 0 ; i < Y_MODIFIER - 1 ; i++) {
			for (int j = 0 ; j < X_MODIFIER - 1 ; j++) {
				dm->printHere(x + j, y + i, ACS_CKBOARD, color);
			}
		}
	}

	void printCursor(DisplayManager *dm) {
		int x = cursor.x * X_MODIFIER + xfrom + 2;
		int y = cursor.y * Y_MODIFIER + yfrom + 2;
		for (int i = 0 ; i < cursor.h * Y_MODIFIER - 1 ; i++) {
			for (int j = 0 ; j < cursor.w * X_MODIFIER - 1 ; j++) {
				dm->printHere(x + j, y + i, ACS_CKBOARD, DisplayManager::CURSOR_COLOR);
			}
		}
	}

	bool checkCursorMove(int xmodifier, int ymodifier) {
		if (cursor.x + xmodifier + cursor.w > MAP_SIZE + 1
			|| cursor.x + xmodifier < 1
			|| cursor.y + ymodifier + cursor.h > MAP_SIZE + 1
			|| cursor.y + ymodifier < 1) {
			return false;
		}
		return true;
	}

	bool checkCursorSwap() {
		if (cursor.x + cursor.h > MAP_SIZE + 1
			|| cursor.y + cursor.w > MAP_SIZE + 1) {
			return false;
		}
		return true;
	}

	bool isThereBoats() {
		int x = 0;
		int y = 0;
		while (x < MAP_SIZE) {
			y = 0;
			while (y < MAP_SIZE) {
				if (map[x][y] == MAP_BOAT) {
					return true;
				}
				y++;
			}
			x++;
		}
		return false;
	}

public:

	int fire() {
		bool hit = false;
		int x = cursor.x - 1;
		int y = cursor.y - 1;
		if (map[x][y] == MAP_FIRED
			|| map[x][y] == MAP_DESTROYED) {
			return ACTION_FAIL;
		} else {
			if (map[x][y] == MAP_WATER) {
				map[x][y] = MAP_FIRED;
			} else if (map[x][y] == MAP_BOAT) {
				map[x][y] = MAP_DESTROYED;
				hit = true;
			}
			if (isThereBoats()) {
				if (hit)
					return ACTION_HIT;
				else
					return CONTINUE;
			} else {
				return END_OF_GAME;
			}
		}
	}

	bool addBoat(DisplayManager *dm, int id) {
		for (int y = 0; y < cursor.h ; y++) {
			for (int x = 0; x < cursor.w ; x++) {
				if (map[cursor.x + x - 1][cursor.y + y - 1] == MAP_BOAT)
					return false;
				map[cursor.x + x - 1][cursor.y + y - 1] = MAP_BOAT;
			}
		}
		boats.push_back(new Boat(dm, Rect(cursor.x - 1, cursor.y - 1, cursor.w, cursor.h),
								id, player, xfrom, yfrom));
		return true;
	}

	void printMap(DisplayManager *dm, int turn) {
		printGrid(dm);
		indicator->print();
		for (int i = 0 ; i < boats.size() ; i++) {
			boats[i]->print(turn);
		}
		printContent(dm, turn);
		printCursor(dm);
	}

	void changeCursorPos(int xmodifier, int ymodifier) {
		if (checkCursorMove(xmodifier, ymodifier)) {
			cursor.x += xmodifier;
			cursor.y += ymodifier;
		}
	}

	void changeCursor(Rect r) {
		cursor.x = r.x;
		cursor.y = r.y;
		cursor.w = r.w;
		cursor.h = r.h;
	}

	void swapCursor(){
		if (checkCursorSwap()) {
			int tmp = cursor.w;
			cursor.w = cursor.h;
			cursor.h = tmp;
		}
	}

	Rect getCursor() {
		return cursor;
	}
};
	
#endif