#ifndef __DISPLAYMANAGER_HPP__
#define __DISPLAYMANAGER_HPP__

#include <ncurses.h>
#include <string.h>

class DisplayManager {
private:

public:

	// Constructors
	DisplayManager() {
		initscr();					/* Start curses mode 		*/
		curs_set(0);				/* Hide cursor				*/
	 	raw();						/* Line buffering disabled	*/
	 	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	 	noecho();					/* Don't echo() while we do getch */
	}

	~DisplayManager() {
		endwin();
	}

	void printHere(int x, int y, int ch) {
		move(x, y);
		addch(ch);
	}

	void printHere(int x, int y, const char *str) {
		int i = 0;
		y -= strlen(str) / 2;
		while (i < strlen(str)) {
			move(x, y);
			addch(str[i]);
			x++;
			i++;
		}
	}
};

#endif