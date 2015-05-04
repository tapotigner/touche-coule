#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include "GameManager.hpp"

int main (int argc, char **argv) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (w.ws_row >= 55 & w.ws_col >= 175) {
		GameManager *gm = new GameManager(w.ws_col, w.ws_row);
		gm->run();
	} else {
		std::cout << "Error, you should resize you terminal terminal to play (55x175 minimum)" << std::endl;
		std::cout << "Your termial size: " << w.ws_col << "x" << w.ws_row << std::endl;
	}
	return (0);
}

// #include <ncurses.h>

// main()
// {
//         initscr();
//         move(0,0);
//         addch('0');
//         move(1,0);
//         addch('1');
//         move(2,0);
//         addch('2');
//         //addstr("this is blink->");
//         addch('H' | A_BLINK);
//         refresh();
//         getch();
//         endwin();
// }