#include "Player.h"
#include <iostream>
#include <string>

int Player::playerCnt = 0;

Player::Player(std::string name)
    : id(playerCnt++),
      name(name),
      HP(100),
      coins(100),
      shovel(1) {
    for (int i =0; i < 4; i++)
        plots.push_back(new Plot());

}

Player::~Player() {
    for (Plot* p: plots)
        delete p;
}

std::ostream& operator<<(std::ostream& out, const Player& obj) {
    out << "Player #" << obj.id + 1 << " " << obj.name;
    return out;
}

void Player::printPlots() const {
    for (Plot* p : plots)
        std::cout << *p;

}

int Player::choosePlot() const {
    printPlots();
    std::cout << "Choose plot index (type 0 to cancel): ";
    int index;
    std::cin >> index;
    std::cin.ignore();
    if (index < 0 || index > (int)plots.size()) {
        std::cout << "Invalid index!";
        return -1;
    }
    return index;
}
