#ifndef __MAP_HPP__
#define __MAP_HPP__

#include "DisplayManager.hpp"

class Map {
private:
	int player;
	int xfrom;
	int yfrom;
	int map[64][64];

public:
	int const MAP_SIZE = 10;
	int const X_MODIFIER = 5;
	int const Y_MODIFIER = 8;
	int const MAP_WATER = 0;
	int const MAP_BOAT = 1;
	int const MAP_FIRED = 2;

	// Constructors
	Map(int p) {
		player = p;
		if (player == 1) {
			xfrom = 1;
			yfrom = 1;
		} else {
			xfrom = 1;
			yfrom = (MAP_SIZE + 1) * Y_MODIFIER;
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
				if (x == 2 + player && y == 2 + player) {
					map[x][y] = MAP_BOAT;
				} else {
					map[x][y] = MAP_WATER;
				}
				y++;
			}
			x++;
		}
	}

	void printGrid(DisplayManager *dm) {
		int x = 0;
		int y = 0;
		while (x < MAP_SIZE * X_MODIFIER + 1) {
			y = 0;
			while (y < MAP_SIZE * Y_MODIFIER + 1) {
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

		while (x < MAP_SIZE) {
			dm->printHere(x*X_MODIFIER + xfrom + X_MODIFIER/2, y*Y_MODIFIER + yfrom + Y_MODIFIER/2, 'A' + x-1);
			x++;
		}
		x = 0;
		y = 1;
		while (y < MAP_SIZE) {
			dm->printHere(x*X_MODIFIER + xfrom + X_MODIFIER/2, y*Y_MODIFIER + yfrom + Y_MODIFIER/2, '1' + y-1);
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
					dm->printHere(x*X_MODIFIER + xfrom + X_MODIFIER/2, y*Y_MODIFIER + yfrom + Y_MODIFIER/2, ACS_DIAMOND);
				} else if (map[x][y] == MAP_FIRED) {
					dm->printHere(x*X_MODIFIER + xfrom + X_MODIFIER/2, y*Y_MODIFIER + yfrom + Y_MODIFIER/2, 'X');
				} 
				y++;
			}
			x++;
		}
	}

public:
	void printMap(DisplayManager *dm) {
		printGrid(dm);
		printIndicator(dm);
		printContent(dm);
	}
};

#endif