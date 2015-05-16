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