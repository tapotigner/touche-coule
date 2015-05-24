#ifndef __BOAT_HPP__
#define __BOAT_HPP__

#include "Rect.hpp"
#include "DisplayManager.hpp"

class Boat {

private:
	int id;
	int player;
	int xfrom;
	int yfrom;
	Rect position;
	DisplayManager *dm;

public:
	Boat(DisplayManager *d, Rect p, int id, int pl, int xf, int yf) {
		position = p;
		dm = d;
		id = id;
		player = pl;
		xfrom = xf;
		yfrom = yf;
	}
	~Boat() {}
	
	void print(int turn) {
		int j = 0;
		int x = 0;
		int y = 0;
		while (x < position.w) {
			y = 0;
			while (y < position.h) {
				if (turn == player) {
					printCase(position.x + x, position.y + y, DisplayManager::BOAT_COLOR);
				} else {
					printCase(position.x + x, position.y + y, DisplayManager::WATER_COLOR);
				}
				y++;
			}
			x++;
		}
		if (turn == player) {
			j = 0;
			while (j < position.w - 1) {
				for (int ii = 0 ; ii < Y_MODIFIER - 1 ; ii++) {
					dm->printHere((position.x + 1) * X_MODIFIER + (1+j) * X_MODIFIER + 1 + xfrom, (position.y + 1) * Y_MODIFIER + ii + 2 + yfrom, ACS_CKBOARD, DisplayManager::BOAT_COLOR);
				}
				j++;
			}
			j = 0;
			while (j < position.h - 1) {
				for (int jj = 0 ; jj < X_MODIFIER - 1 ; jj++) {
					dm->printHere((position.x + 1) * X_MODIFIER + jj + 2 + xfrom, (position.y + 1) * Y_MODIFIER + (1+j) * Y_MODIFIER + 1 + yfrom, ACS_CKBOARD, DisplayManager::BOAT_COLOR);
				}
				j++;
			}
		}
	}

	void printCase(int x, int y, int color) {
		x = x * X_MODIFIER + xfrom + 2 + X_MODIFIER;
		y = y * Y_MODIFIER + yfrom + 2 + Y_MODIFIER;
		for (int i = 0 ; i < Y_MODIFIER - 1 ; i++) {
			for (int j = 0 ; j < X_MODIFIER - 1 ; j++) {
				dm->printHere(x + j, y + i, ACS_CKBOARD, color);
			}
		}
	}
};

#endif