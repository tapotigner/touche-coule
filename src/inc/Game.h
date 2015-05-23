#ifndef __GAME_H__
#define __GAME_H__

// CONF
static const int BOATS_TEMPLATE[] = {2, 3};
static const int NB_BOATS = 2;

// VARS
static const int TURN_P1 = 1;
static const int TURN_P2 = -1;

// ACTIONS
static const int ACTION_FAIL = 42;
static const int END_OF_GAME = 43;
static const int CONTINUE = 44;
static const int ACTION_HIT = 45;

// INPUTS
static const int UP = 259;
static const int DOWN = 258;
static const int LEFT = 260;
static const int RIGHT = 261;
static const int ENTER = 10;
static const int ESCAPE = 27;
static const int SPACE = 32;
static const int CTRLC = 3;

#endif