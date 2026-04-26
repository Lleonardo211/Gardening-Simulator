#ifndef GARDENINGSIMULATOR_PLAYER_H
#define GARDENINGSIMULATOR_PLAYER_H

#include "Store.h"
#include "Plot.h"
#include "Shovel.h"
#include "Tank.h"
#include <iostream>
#include <string>
#include <vector>

class Player {
private:
    static int playerCnt;
    const int id;
    std::string name;
    int currentWeek;
    int HP;
    int medkits;
    int coins;
    std::vector<Plot*> plots;
    Shovel shovel;
    Tank tank;
    int potatoSeeds;
    int tomatoSeeds;
    int potatoCrates;
    int tomatoCrates;
    int fertilizer;
    int atomicFertilizer;

    void printPlots() const;
    void decreaseSeeds(int seedType);
    int calculateYield(int plotIdx) const;

public:
    Player(const std::string& name);
    ~Player();

    void printStats() const;

    void printPlotStats(int plotIdx) const;
    int choosePlot() const;
    bool growthCheck(int plotIdx) const { return plots[plotIdx] -> getPlantGrowth(); }
    bool emptyCheck(int plotIdx) const;
    void emptyPlot(int plotIdx) const;

    void setWeather() const;
    void updateCrops() const;

    void harvest(int plotIdx);

    void plantSeeds(int plotIdx, int seedType);

    int waterPlant(int plotIdx);

    void fillWaterTank();

    void fertilize(int plotIdx, int fertilizerType);
    bool fertilizationCheck(int plotIdx) const { return plots[plotIdx] -> getFertilization(); }

    void buy(Store& store, int product);
    void upgradeShovel(Store& store);
    void upgradeTank(Store& store);

    void sellPotatoes(Store& store, int amount);
    void sellTomatoes(Store& store, int amount);

    int getCurrentWeek() const{ return currentWeek; }
    int getPotatoSeeds() const{ return potatoSeeds; }
    int getTomatoSeeds() const{ return tomatoSeeds; }
    int getPotatoCrates() const{ return potatoCrates; }
    int getTomatoCrates() const{ return tomatoCrates; }
    int getFertilizer() const{ return fertilizer; }
    int getAtomicFertilizer() const{ return atomicFertilizer; }

    void setCurrentWeek(int newIdx) { currentWeek = newIdx; }
    void setCoins(int coinCnt) { coins = coinCnt; }

    friend std::ostream& operator<<(std::ostream& out, const Player& obj);

};



#endif //GARDENINGSIMULATOR_PLAYER_H
