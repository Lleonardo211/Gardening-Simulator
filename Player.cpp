#include "Player.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <random>

int Player::playerCnt = 0;

Player::Player(const std::string& name)
    : id(playerCnt++),
      name(name),
      currentWeek(1),
      HP(100),
      coins(100),
      shovel(1),
      tank(),
      potatoSeeds(0),
      tomatoSeeds(1),
      potatoCrates(0),
      tomatoCrates(0),
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

void Player::printStats() const {
    std::cout << "HP: " << HP << '\n';
    std::cout << "Coins: " << coins << '\n';
    std::cout << "potato crates: " << potatoCrates << '\n';
    std::cout << "tomato crates: " << tomatoCrates << '\n';
    std::cout << "\nequipment:\n";
    std::cout << shovel << '\n';
    std::cout << tank << '\n';

    std::cin.get();
}

void Player::setWeather() {
    Plot::calculateWeather();
    for (Plot* p: plots)
        p -> setWaterLevel(Plot::getRainLevel());
}

void Player::updateCrops() const {
    for (Plot* p: plots)
        p -> growPlant();
}

void Player::printPlotStats(int plotIdx) const {
    plots[plotIdx] -> printPlant();
    std::cout << "water level: " << plots[plotIdx] -> getWaterLevel() << '\n';
    std::cout << "sunlight level: " << plots[plotIdx] -> getSunlightLevel() << '\n';
    if (plots[plotIdx] -> getFertilization())
        std::cout << "fertilized\n\n";
    else
        std::cout << "not fertilized\n\n";
}

void Player::printPlots() const {
    for (Plot* p : plots)
        std::cout << *p << '\n';
}

int Player::choosePlot() const {
    std::cout << "Available land plots:\n\n";
    printPlots();
    std::cout << "Choose plot index (type 0 to cancel): ";
    int index;
    std::cin >> index;
    std::cin.ignore();
    if (index < 0 || index > static_cast<int>(plots.size())) {
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
            break;
        }
        case 2: {
            tomatoSeeds--;
            break;
        }
        default: {
            std::cout << "Invalid seed type!";
            std::cin.get();
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

bool Player::emptyCheck(int plotIdx) const {
   return plots[plotIdx] -> empty();
}

void Player::emptyPlot(int plotIdx) const {
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
    tank.setWaterVolume(remainder);
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

int Player::calculateYield(int plotIdx) const{
    int crateCnt;

    static std::random_device seed;
    static std::mt19937 gen(seed());

    if (plots[plotIdx] -> getRadioactivity() == 1) {

        std::normal_distribution<> atomicDist(7.5,1);
        crateCnt = std::clamp(static_cast<int>(std::round(atomicDist(gen))), 5, 10);
        return crateCnt;
    }
    int sunlightLevel = Plot::getSunlightLevel();
    double mean = 2.5 + (sunlightLevel / 10.0) * 2.5;
    std::normal_distribution<> normalDist(mean,1);
    crateCnt = std::clamp(static_cast<int>(std::round(normalDist(gen))), 2, 5);
    return crateCnt;
}

void Player::harvest(int plotIdx) {
    int crateCnt = calculateYield(plotIdx);
    if (plots[plotIdx] -> getPlant() == "potato") {
        potatoCrates += crateCnt;
    } else {
        tomatoCrates += crateCnt;
    }
    emptyPlot(plotIdx);
}



