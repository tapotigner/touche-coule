#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Map.hpp"

class Player {
private:
	Map	*opponentMap;
	Map	*myMap;
public:
	Player() {
		myMap = new Map();
		opponentMap = new ();
	}
	~Player() {

	}
	
};

#endif