#ifndef __SPLASHSCREENPROCESS_HPP__
#define __SPLASHSCREENPROCESS_HPP__

#include <string>
#include "Process.hpp"
#include "DisplayManager.hpp"
#include "Rect.hpp"

class SplashScreenProcess : public Process {
public:
	SplashScreenProcess(DisplayManager *dm, Rect winSize) : Process(dm, winSize) {}
	~SplashScreenProcess() {}
	
	void init() {

	}

	bool run() {
		erase();
		std::string str = "Welcome to navy battle. Press a key to continue...";
		std::string str0 = "                                                                                                             ";
		std::string str1 = "  __    __     _                            _                                    _           _   _   _       ";
		std::string str2 = " / / /\\ \\ \\___| | ___ ___  _ __ ___   ___  | |_ ___    _ __   __ ___   ___   _  | |__   __ _| |_| |_| | ___  ";
		std::string str3 = " \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  | '_ \\ / _` \\ \\ / / | | | | '_ \\ / _` | __| __| |/ _ \\ ";
		std::string str4 = "  \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | | | | (_| |\\ V /| |_| | | |_) | (_| | |_| |_| |  __/ ";
		std::string str5 = "   \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/  |_| |_|\\__,_| \\_/  \\__, | |_.__/ \\__,_|\\__|\\__|_|\\___| ";
		std::string str6 = "                                                                         |___/                               ";
		displayManager->printHere(winSize.x / 2, winSize.y / 2 - 4, str0.c_str(), DisplayManager::SPLASH_SCREEN_BORDER);
		displayManager->printHere(winSize.x / 2, winSize.y / 2 - 3, str0.c_str(), DisplayManager::SPLASH_SCREEN_TEXT);
		displayManager->printHere(winSize.x / 2, winSize.y / 2 - 2, str1.c_str(), DisplayManager::SPLASH_SCREEN_TEXT);
		displayManager->printHere(winSize.x / 2, winSize.y / 2 - 1, str2.c_str(), DisplayManager::SPLASH_SCREEN_TEXT);
		displayManager->printHere(winSize.x / 2, winSize.y / 2, str3.c_str(), DisplayManager::SPLASH_SCREEN_TEXT);
		displayManager->printHere(winSize.x / 2, winSize.y / 2 + 1, str4.c_str(), DisplayManager::SPLASH_SCREEN_TEXT);
		displayManager->printHere(winSize.x / 2, winSize.y / 2 + 2, str5.c_str(), DisplayManager::SPLASH_SCREEN_TEXT);
		displayManager->printHere(winSize.x / 2, winSize.y / 2 + 3, str6.c_str(), DisplayManager::SPLASH_SCREEN_TEXT);
		displayManager->printHere(winSize.x / 2, winSize.y / 2 + 4, str0.c_str(), DisplayManager::SPLASH_SCREEN_TEXT);
		displayManager->printHere(winSize.x / 2, winSize.y / 2 + 5, str0.c_str(), DisplayManager::SPLASH_SCREEN_BORDER);
		refresh();
		getch();
	}

// " __    __     _                            _                                    _           _   _   _      "
// "/ / /\ \ \___| | ___ ___  _ __ ___   ___  | |_ ___    _ __   __ ___   ___   _  | |__   __ _| |_| |_| | ___ "
// "\ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \  | '_ \ / _` \ \ / / | | | | '_ \ / _` | __| __| |/ _ \"
// " \  /\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | | | | (_| |\ V /| |_| | | |_) | (_| | |_| |_| |  __/"
// "  \/  \/ \___|_|\___\___/|_| |_| |_|\___|  \__\___/  |_| |_|\__,_| \_/  \__, | |_.__/ \__,_|\__|\__|_|\___|"
// "                                                                        |___/                              "


	void end() {

	}

};

#endif