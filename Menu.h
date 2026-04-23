#ifndef GARDENINGSIMULATOR_MENU_H
#define GARDENINGSIMULATOR_MENU_H

#include "Player.h"
#include <vector>

class Menu {
private:
    std::vector<Player*> players;

public:
    Menu() = default;
    void mainMenu();
    void gardenMenu(int index);
    void storeMenu(int index);
    void gardeningMenu(int index);

    void printPlayers() const;
    int choosePlayer() const;

};

#endif //GARDENINGSIMULATOR_MENU_H
