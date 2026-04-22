
#ifndef GARDENINGSIMULATOR_PLAYER_H
#define GARDENINGSIMULATOR_PLAYER_H

#include <iostream>
#include <string>

class Player {
private:
    static int playerCnt;
    const int id;
    std::string name;
    int coins;
    //Garden garden;
    //Shovel shovel;

public:
    Player(std::string name);
    ~Player();

    friend std::istream& operator>>(std::istream& in, Player& obj);
    friend std::ostream& operator<<(std::ostream& out, const Player& obj);

};



#endif //GARDENINGSIMULATOR_PLAYER_H
