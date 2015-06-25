#ifndef __GAMEMANAGER_HPP__
#define __GAMEMANAGER_HPP__

#include <stdlib.h>
#include <string>
#include "Utils.hpp"
#include "DisplayManager.hpp"
#include "FightProcess.hpp"
#include "PlaceBoatProcess.hpp"
#include "SplashScreenProcess.hpp"
#include "Map.hpp"
#include "Game.h"

class GameManager {
private:
	DisplayManager 	*displayManager;
	NetworkManager	*networkManager;
	Map 			*map1;
	Map 			*map2;
	bool			playing;
	Rect 			winSize;
	bool 			myturn;

public:

	// Constructors
	GameManager(int x, int y) {
		displayManager = new DisplayManager();
		networkManager = new NetworkManager(4242);
		map1 = new Map(TURN_P1, displayManager);
		map2 = new Map(TURN_P2, displayManager);
		playing = true;
		winSize = Rect(0, 0, 0, 0);
		winSize.x = x;
		winSize.y = y;
	}

	~GameManager() {

	}

	void run() {
		myturn = networkManager->run();
		runGame();
		closeGame();
	}

private:

	void runGame() {
		splashScreen();
		if (playing) placeBoats();
		//if (playing) fight();
	}

	void splashScreen() {
		SplashScreenProcess ssp = SplashScreenProcess(displayManager, winSize);
		ssp.init();
		ssp.run();
		ssp.end();
	}

	bool fight() {
		FightProcess fp = FightProcess(displayManager, map1, map2, playing, winSize);
		fp.init();
		playing = fp.run();
		fp.end();

		return (playing);
	}

	bool placeBoats() {
		PlaceBoatProcess pbp = PlaceBoatProcess(displayManager, map1, map2, playing, winSize, myturn);
		pbp.init();
		playing = pbp.run();
		pbp.end();

		return (playing);
	}

	void closeGame() {
		delete (map1);
		delete (map2);
		delete (displayManager);
		playing = false;
	}
};

#endif