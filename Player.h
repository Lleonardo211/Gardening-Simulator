#ifndef GARDENINGSIMULATOR_PLAYER_H
#define GARDENINGSIMULATOR_PLAYER_H

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

public:
    Player(const std::string& name);
    ~Player();

    void printStats() const;

    void printPlots() const;
    void printPlotStats(int plotIdx) const;
    int choosePlot() const;
    bool growthCheck(int plotIdx) const { return plots[plotIdx] -> getPlantGrowth(); }
    bool emptyCheck(int plotIdx) const;
    void emptyPlot(int plotIdx) const;

    void setWeather();
    void updateCrops() const;

    int calculateYield(int plotIdx) const;
    void harvest(int plotIdx);

    void plantSeeds(int plotIdx, int seedType);
    void decreaseSeeds(int seedType);

    int waterPlant(int plotIdx);

    void fertilize(int plotIdx, int fertilizerType);
    bool fertilizationCheck(int plotIdx) const { return plots[plotIdx] -> getFertilization(); }

    int getCurrentWeek() const{ return currentWeek; }
    int getPotatoSeeds() const{ return potatoSeeds; }
    int getTomatoSeeds() const{ return tomatoSeeds; }
    int getFertilizer() const{ return fertilizer; }
    int getAtomicFertilizer() const{ return atomicFertilizer; }

    void setCurrentWeek(int newIdx) { currentWeek = newIdx; }

    friend std::ostream& operator<<(std::ostream& out, const Player& obj);

};



#endif //GARDENINGSIMULATOR_PLAYER_H
