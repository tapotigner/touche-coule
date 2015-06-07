#ifndef __DISPLAYMANAGER_HPP__
#define __DISPLAYMANAGER_HPP__

#include <ncurses.h>
#include <string.h>

class DisplayManager {
private:
public:
	
	enum Color { SPLASH_SCREEN_TEXT = 9, SPLASH_SCREEN_BORDER = 10, INDIC = 11, GRID_COLOR = 12, WATER_COLOR = 13, BOAT_COLOR = 14,
					FIRED_COLOR = 15, DESTROYED_COLOR = 16, CURSOR_COLOR = 1};
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
  		nodelay(stdscr,TRUE);		/* No bloquant getch() */
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

	void printHere(int x, int y, const char *str, int color, int style) {
		x -= strlen(str) / 2;
		attron(COLOR_PAIR(color));
		attron(style);
		move(y, x);
		addstr(str);
		attroff(COLOR_PAIR(color));
		attroff(style);
	}

private:
	void initColor() {
		init_pair(CURSOR_COLOR, COLOR_BLACK, COLOR_GREEN);
    	init_pair(SPLASH_SCREEN_TEXT, COLOR_MAGENTA, COLOR_WHITE);
    	init_pair(SPLASH_SCREEN_BORDER, COLOR_RED, COLOR_RED);
    	init_pair(INDIC, COLOR_WHITE, COLOR_BLACK);
    	init_pair(GRID_COLOR, COLOR_BLACK, COLOR_BLACK);
    	init_pair(WATER_COLOR, COLOR_BLACK, COLOR_CYAN);
    	init_pair(BOAT_COLOR, COLOR_BLACK, COLOR_WHITE);
    	init_pair(DESTROYED_COLOR, COLOR_BLACK, COLOR_RED);
    	init_pair(FIRED_COLOR, COLOR_BLACK, COLOR_BLUE);
	}
// COLOR_BLACK   0
// COLOR_RED     1
// COLOR_GREEN   2
// COLOR_YELLOW  3
// COLOR_BLUE    4
// COLOR_MAGENTA 5
// COLOR_CYAN    6
// COLOR_WHITE   7
};

#endif