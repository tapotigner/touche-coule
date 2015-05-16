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
	const int MAP_SIZE = 9;
	const int X_MODIFIER = 8;
	const int Y_MODIFIER = 5;
	const int MAP_WATER = 0;
	const int MAP_BOAT = 1;
	const int MAP_FIRED = 2;
	static const int BOATS_TEMPLATE[];
	static const int NB_BOATS = 5;

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
				if (x % X_MODIFIER == 0 || y % Y_MODIFIER == 0) {
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
		int posx, posy, indic;

		while (x <= MAP_SIZE) {
			posx = x*X_MODIFIER + xfrom + X_MODIFIER/2;
			posy = y*Y_MODIFIER + yfrom + Y_MODIFIER/2;
			indic = '1' + x-1;
			dm->printHere(posx, posy, indic, DisplayManager::BLACK);
			x++;
		}
		x = 0;
		y = 1;
		while (y <= MAP_SIZE) {
			posx = x*X_MODIFIER + xfrom + X_MODIFIER/2;
			posy = y*Y_MODIFIER + yfrom + Y_MODIFIER/2;
			indic = 'A' + y-1;
			dm->printHere(posx, posy, indic, DisplayManager::BLACK);
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
					printCase(dm, x, y, DisplayManager::BLACK);
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
		for (int i = 0 ; i < Y_MODIFIER ; i++) {
			for (int j = 0 ; j < X_MODIFIER ; j++) {
				dm->printHere(x + j, y + i, ACS_CKBOARD, color);
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

	bool addBoat() {
		for (int y = 0; y < cursor.h ; y++) {
			for (int x = 0; x < cursor.w ; x++) {
				if (map[cursor.x + x - 1][cursor.y + y - 1] == MAP_BOAT)
					return false;
			}
		}
		for (int y = 0; y < cursor.h ; y++) {
			for (int x = 0; x < cursor.w ; x++) {
				map[cursor.x + x - 1][cursor.y + y - 1] = MAP_BOAT;
			}
		}
		return true;
	}

	void printMap(DisplayManager *dm) {
		printContent(dm);
		printCursor(dm);
		printGrid(dm);
		printIndicator(dm);
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
};

const int Map::BOATS_TEMPLATE[] = {5, 4, 3, 3, 2};

#endif