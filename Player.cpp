#include "Player.h"
#include <iostream>
#include <string>

int Player::playerCnt = 0;

Player::Player(std::string name)
    : id(playerCnt++),
      name(name),
      HP(100),
      coins(100),
      shovel(1),
      tank(),
      tomatoSeeds(1),
      potatoSeeds(0),
      fertilizer(2),
      atomicFertilizer(1){
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

void Player::printPlotStats(int plotIdx) const {
    std::cout << "water level: " << plots[plotIdx] -> getWaterLevel() << '\n';
    std::cout << "sunlight level: " << plots[plotIdx] -> getSunlightLevel() << '\n';
    if (plots[plotIdx] -> getFertilization())
        std::cout << "fertilized\n";
    else
        std::cout << "not fertilized\n";
}

void Player::printPlots() const {
    for (Plot* p : plots)
        std::cout << *p << '\n';
}

int Player::choosePlot() const {
    printPlots();
    std::cout << "Choose plot index (type 0 to cancel): ";
    int index;
    std::cin >> index;
    std::cin.ignore();
    if (index < 0 || index > (int)plots.size()) {
        std::cout << "\nInvalid index!";
        std::cin.get();
        return -1;
    }
    return index;
}

void Player::decreaseSeeds(int seedType) {
    switch (seedType) {
        case 1: {
            potatoSeeds--;
        }
        case 2: {
            tomatoSeeds--;
        }
    }
}

void Player::plantSeeds(int plotIdx, int seedType) {
    if (plots[plotIdx] -> empty()) {
        plots[plotIdx] -> assignPlant(seedType);
        decreaseSeeds(seedType);
    } else {
        std::cout << "\nThis plot is currently occupied!\n";
        std::cin.get();
    }
}

void Player::emptyPlot(int plotIdx) {
    plots[plotIdx] -> removePlant();
}

int Player::waterPlant(int plotIdx) {
    int waterVolume = tank.getWaterVolume();
    int plotWaterLevel = plots[plotIdx] -> getWaterLevel();
    if (waterVolume == 0 )
        return -1;
    if (plotWaterLevel == 300)
        return -2;
    int remainder = plots[plotIdx] -> increaseWaterLevel(waterVolume);
    waterVolume = remainder;
    return 0;
}

void Player::fertilize(int plotIdx, int fertilizerType) {
    plots[plotIdx] -> increaseFertilization();
    if (fertilizerType == 2) {
        plots[plotIdx] -> increaseRadioactivity();
        atomicFertilizer--;
    } else {
        fertilizer--;
    }
}



