#include "../include/enemy.h"

// class Enemy
Enemy::Enemy(){}
Enemy::Enemy(Coord pos, std::string symbol, int lives, bool alive, int speed) : Personaje(pos, symbol, lives, speed){
    Enemy::alive = alive;
};

Enemy::Enemy(Enemy &o) : Personaje(o) 
{
    alive = o.alive;
}

bool Enemy::isAlive(){ return alive; }

void Enemy::setAlive(bool alive) { this->alive = alive; }

void Enemy::setRandomDirection() {
    srand(time(NULL));
    int x = rand() % 4 + 1;
    switch (x) {
        case 1:
            direction = Directions::UP;
            break;
        case 2:
            direction = Directions::DOWN;
            break;
        case 3:
            direction = Directions::RIGHT;
            break;
        case 4:
            direction = Directions::LEFT;
            break;
    }
}

void Enemy::printAttributes()
{
    Personaje::printAttributes();
    std::cout << "Alive: " << alive << std::endl;
}

// class Normal Enemy

NormalEnemy::NormalEnemy(Coord _pos, char _symbol, int lives = 1, bool alive = true, int speed = 1):Enemy(pos, symbol, lives, alive, speed){}

void NormalEnemy::move(){
       
}
