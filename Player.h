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
    int HP;
    int coins;
    std::vector<Plot*> plots;
    Shovel shovel;
    Tank tank;
    int potatoSeeds;
    int tomatoSeeds;
    int fertilizer;
    int atomicFertilizer;

public:
    Player(std::string name);
    ~Player();

    void printPlots() const;
    void printPlotStats(int plotIdx) const;
    int choosePlot() const;
    void emptyPlot(int plotIdx);

    void plantSeeds(int plotIdx, int seedType);
    void decreaseSeeds(int seedType);

    int waterPlant(int plotIdx);

    void fertilize(int plotIdx, int fertilizerType);
    bool fertilizationCheck(int plotIdx) { return plots[plotIdx] -> getFertilization(); }

    int getPotatoSeeds() { return potatoSeeds; }
    int getTomatoSeeds() { return tomatoSeeds; }
    int getFertilizer() { return fertilizer; }
    int getAtomicFertilizer() { return atomicFertilizer; }

    friend std::ostream& operator<<(std::ostream& out, const Player& obj);

};



#endif //GARDENINGSIMULATOR_PLAYER_H
