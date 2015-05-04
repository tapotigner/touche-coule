#ifndef __MAP_HPP__
#define __MAP_HPP__

#include "DisplayManager.hpp"
#include "Rect.hpp"

class Map {
private:
	int player;
	int xfrom;
	int yfrom;
	int map[64][64];
	Rect cursor = Rect(0, 0, 0, 0);

public:
	const int MAP_SIZE = 3;
	const int X_MODIFIER = 8;
	const int Y_MODIFIER = 5;
	const int MAP_WATER = 0;
	const int MAP_BOAT = 1;
	const int MAP_FIRED = 2;

	// Constructors
	Map(int p) {
		player = p;
		if (player == 1) {
			xfrom = 1;
			yfrom = 1;
		} else {
			xfrom = (MAP_SIZE + 1) * X_MODIFIER + (2 * X_MODIFIER);
			yfrom = 1;
		}
		init();
	}

	~Map() {

	}

private:
	void init() {
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
	}

	void printGrid(DisplayManager *dm) {
		int x = 0;
		int y = 0;
		while (x < (MAP_SIZE + 1) * X_MODIFIER + 1) {
			y = 0;
			while (y < (MAP_SIZE + 1) * Y_MODIFIER + 1) {
				if (x % X_MODIFIER == 0) {
					dm->printHere(x+xfrom, y+yfrom, ACS_CKBOARD);
				} else if (y % Y_MODIFIER == 0) {
					dm->printHere(x+xfrom, y+yfrom, ACS_CKBOARD);
				}
				y++;
			}
			x++;
		}
	}

	void printIndicator(DisplayManager *dm) {
		int x = 1;
		int y = 0;

		while (x <= MAP_SIZE) {
			dm->printHere(x*X_MODIFIER + xfrom + X_MODIFIER/2, y*Y_MODIFIER + yfrom + Y_MODIFIER/2, '1' + x-1);
			x++;
		}
		x = 0;
		y = 1;
		while (y <= MAP_SIZE) {
			dm->printHere(x*X_MODIFIER + xfrom + X_MODIFIER/2, y*Y_MODIFIER + yfrom + Y_MODIFIER/2, 'A' + y-1);
			y++;
		}
	}

	void printContent(DisplayManager *dm) {
		int x = 0;
		int y = 0;
		while (x < MAP_SIZE) {
			y = 0;
			while (y < MAP_SIZE) {
				if (map[x][y] == MAP_BOAT) {
					printCase(dm, x, y, DisplayManager::GREEN);
				} else if (map[x][y] == MAP_FIRED) {
					printCase(dm, x, y, DisplayManager::RED);
				} else {
					printCase(dm, x, y, DisplayManager::BLUE);
				}
				y++;
			}
			x++;
		}
	}

	void printCase(DisplayManager *dm, int x, int y, int color) {
		x = x * X_MODIFIER + xfrom + 1 + X_MODIFIER;
		y = y * Y_MODIFIER + yfrom + 1 + Y_MODIFIER;
		for (int i = 0 ; i < cursor.h * Y_MODIFIER ; i++) {
			for (int j = 0 ; j < cursor.w * X_MODIFIER ; j++) {
				dm->printHere(x, y, ACS_CKBOARD, color);
			}
		}
	}

	void printCursor(DisplayManager *dm) {
		int x = cursor.x * X_MODIFIER + xfrom + 1;
		int y = cursor.y * Y_MODIFIER + yfrom + 1;
		for (int i = 0 ; i < cursor.h * Y_MODIFIER ; i++) {
			for (int j = 0 ; j < cursor.w * X_MODIFIER ; j++) {
				dm->printHere(x + j, y + i, ACS_CKBOARD, DisplayManager::GREEN);
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

public:
	void printMap(DisplayManager *dm) {
		printCursor(dm);
		printGrid(dm);
		printIndicator(dm);
		printContent(dm);
	}

	void changeCursorPos(int xmodifier, int ymodifier) {
		if (checkCursorMove(xmodifier, ymodifier)) {
			cursor.x += xmodifier;
			cursor.y += ymodifier;
		}
	}

	void changeCursor(Rect r) {
		cursor.x += r.x;
		cursor.y += r.y;
		cursor.w += r.w;
		cursor.h += r.h;
	}

	void swapCursor(){
		if (checkCursorSwap()) {
			int tmp = cursor.w;
			cursor.w = cursor.h;
			cursor.h = tmp;
		}
	}
};

#endif