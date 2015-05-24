#ifndef __INDICATOR_HPP__
#define __INDICATOR_HPP__

#include "Map.hpp"
#include "Game.h"

class Map;

class Indicator
{
private:
	DisplayManager *dm;
	int xfrom;
	int yfrom;
public:
	Indicator(DisplayManager *d, int xf, int yf) {
		dm = d;
		xfrom = xf;
		yfrom = yf;
	}
	~Indicator();

	void print() {
		int x = 1;
		int y = 0;
		int posx, posy, indic;

		while (x <= MAP_SIZE) {
			posx = x*X_MODIFIER + xfrom + X_MODIFIER/2;
			posy = y*Y_MODIFIER + yfrom + Y_MODIFIER/2;
			indic = '1' + x-1;
			printThisIndicator(indic, posx, posy);
			x++;
		}
		x = 0;
		y = 1;
		while (y <= MAP_SIZE) {
			posx = x*X_MODIFIER + xfrom + X_MODIFIER/2;
			posy = y*Y_MODIFIER + yfrom + Y_MODIFIER/2;
			indic = 'A' + y-1;
			printThisIndicator(indic, posx, posy);
			y++;
		}
	}

	void printThisIndicator(int indic, int posx, int posy) {
		std::string s1 = "";
		std::string s2 = "";
		std::string s3 = "";
		std::string s4 = "";
		if (indic == 'A') {
			s1 = "       ";
			s2 = "   /\\  ";
			s3 = "  /--\\ ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);
		} else if (indic == 'B') {
			s1 = "   __  ";
			s2 = "  |__) ";
			s3 = "  |__) ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);
		} else if (indic == 'C') {
			s1 = "   __  ";
			s2 = "  /    ";
			s3 = "  \\__  ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);
		} else if (indic == 'D') {
			s1 = "   __  ";
			s2 = "  |  \\ ";
			s3 = "  |__/ ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);
		} else if (indic == 'E') {
			s1 = "   __  ";
			s2 = "  |_   ";
			s3 = "  |__  ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);
		} else if (indic == 'F') {
			s1 = "   __  ";
			s2 = "  |_   ";
			s3 = "  |    ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);
		} else if (indic == 'G') {
			s1 = "   __  ";
			s2 = "  / _  ";
			s3 = "  \\__) ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);
		} else if (indic == 'H') {
			s1 = "       ";
			s2 = "  |__| ";
			s3 = "  |  | ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);
		} else if (indic == 'I') {
			s1 = "       ";
			s2 = "   |   ";
			s3 = "   |   ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);
		} else if (indic == '1') {
			s1 = "       ";
			s2 = "  /|   ";
			s3 = "   |   ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);

		} else if (indic == '2') {
			s1 = "  __   ";
			s2 = "   _)  ";
			s3 = "  /__  ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);

		} else if (indic == '3') {
			s1 = "  __   ";
			s2 = "   _)  ";
			s3 = "  __)  ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);

		} else if (indic == '4') {
			s1 = "       ";
			s2 = " |__|  ";
			s3 = "    |  ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);

		} else if (indic == '5') {
			s1 = "   __  ";
			s2 = "  |_   ";
			s3 = "  __)  ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);

		} else if (indic == '6') {
			s1 = "  __   ";
			s2 = " /__   ";
			s3 = " \\__)  ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);

		} else if (indic == '7') {
			s1 = "  ___  ";
			s2 = "    /  ";
			s3 = "   /   ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);

		} else if (indic == '8') {
			s1 = "  __   ";
			s2 = " (__)  ";
			s3 = " (__)  ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);

		} else if (indic == '9') {
			s1 = "  __   ";
			s2 = " (__\\  ";
			s3 = "  __/  ";
			s4 = "       ";
			printLetters(posx, posy, s1, s2, s3, s4);

		} else {
			dm->printHere(posx, posy, indic, DisplayManager::INDIC);
		}
	}
      
	void printLetters(int posx, int posy, std::string s1, std::string s2 ,std::string s3, std::string s4) {
		dm->printHere(posx, posy-1, s1.c_str(), DisplayManager::INDIC, DisplayManager::BOLD);
		dm->printHere(posx, posy, s2.c_str(), DisplayManager::INDIC, DisplayManager::BOLD);
		dm->printHere(posx, posy+1, s3.c_str(), DisplayManager::INDIC, DisplayManager::BOLD);
		dm->printHere(posx, posy+2, s4.c_str(), DisplayManager::INDIC, DisplayManager::BOLD);
	}
	
};

#endif