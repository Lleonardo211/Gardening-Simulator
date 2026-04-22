#include "Player.h"
#include <iostream>
#include <string>

int Player::playerCnt = 0;

Player::Player(std::string name) : id(playerCnt++) {
    this->name = name;
    this->coins = 100;
}

Player::~Player() {

}

std::ostream& operator<<(std::ostream& out, const Player& obj) {
    out << "Player #" << obj.id + 1 << " " << obj.name;
    return out;
}