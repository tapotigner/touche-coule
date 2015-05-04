#ifndef __DISPLAYMANAGER_HPP__
#define __DISPLAYMANAGER_HPP__

#include <ncurses.h>
#include <string.h>

// attron(A_BOLD);
// attron(A_BLINK);
// attron(A_NORMAL);

class DisplayManager {
private:

public:
	enum Color { WHITE = 1, RED = 2, GREEN = 3, BLUE = 4, BLACK = 5};	
	enum Style { NORMAL = A_NORMAL, BLINK = A_BLINK, BOLD = A_BOLD};	

	// Constructors
	DisplayManager() {
		initscr();					/* Start curses mode 		*/
		curs_set(0);				/* Hide cursor				*/
	 	raw();						/* Line buffering disabled	*/
	 	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	 	noecho();					/* Don't echo() while we do getch */
	 	start_color();				/* Colors */
	 	initColor();				/* Init color pairs */
	}

	~DisplayManager() {
		endwin();
	}

	void printHere(int x, int y, int ch) {
		move(y, x);
		addch(ch);
	}

	void printHere(int x, int y, const char *str) {
		x -= strlen(str) / 2;
		move(y, x);
		addstr(str);
	}

	void printHere(int x, int y, int ch, int color) {
		attron(COLOR_PAIR(color));
		move(y, x);
		addch(ch);
		attron(COLOR_PAIR(1));
	}

	void printHere(int x, int y, const char *str, int color) {
		x -= strlen(str) / 2;
		attron(COLOR_PAIR(color));
		move(y, x);
		addstr(str);
		attron(COLOR_PAIR(1));
	}

private:
	void initColor() {
		init_pair(1, COLOR_BLACK, COLOR_WHITE);
    	init_pair(2, COLOR_BLACK, COLOR_RED);
    	init_pair(3, COLOR_BLACK, COLOR_GREEN);
    	init_pair(4, COLOR_BLACK, COLOR_BLUE);
    	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	}
};

#endif