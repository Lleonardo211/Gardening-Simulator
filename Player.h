#ifndef GARDENINGSIMULATOR_PLAYER_H
#define GARDENINGSIMULATOR_PLAYER_H

#include "Plot.h"
#include "Shovel.h"
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

public:
    Player(std::string name);
    ~Player();

    void printPlots() const;
    int choosePlot() const;

    friend std::ostream& operator<<(std::ostream& out, const Player& obj);

};



#endif //GARDENINGSIMULATOR_PLAYER_H
