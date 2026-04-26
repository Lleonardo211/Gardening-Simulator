#ifndef GARDENINGSIMULATOR_MENU_H
#define GARDENINGSIMULATOR_MENU_H

#include "Player.h"
#include "Store.h"
#include <vector>

class Menu {
private:
    std::vector<Player*> players;
    Store store;

    void loadPlayers();
    void savePlayers() const;

    void gardenMenu(int index);
    void storeMenu(int index);
    bool unlucky() const;
    void gardeningMenu(int playerIdx, int plotIdx);
    bool skip(int playerIdx);
    void buy(int playerIdx);
    void sell(int playerIdx);
    void gameOver(int playerIdx);

    void printPlayers() const;
    int choosePlayer() const;

    int chooseSeeds(int playerIdx) const;

    int chooseFertilizer(int playerIdx) const;

public:
    Menu() = default;
    ~Menu();
    void mainMenu();

};

#endif //GARDENINGSIMULATOR_MENU_H
