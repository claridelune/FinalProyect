#ifndef PLAYER
#define PLAYER

#include "personaje.h"

class Player : public Personaje {
public:
    int level_score;
    int total_score;
    int bulletCount;

    Player(int row, int col, char symbol, int bulletCount = 5, int lives = 1, int speed = 1, int level_score = 0, int total_score = 0);
};

#endif
