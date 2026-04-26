#ifndef GARDENINGSIMULATOR_POTATO_H
#define GARDENINGSIMULATOR_POTATO_H


#include "Plant.h"
#include <iostream>
#include <string>

class Player;

class Potato : public Plant {
public:
    Potato() : Plant(false, 60, 8 , 10) {}
    Potato(const Potato& obj);
    Potato& operator=(const Potato& obj);
    ~Potato() override;

    std::string plantType() const override;
    void plantAttack(Player *player) override;
    void lightAttack(Player* player) override;
    void normalAttack(Player* player) override;
    void heavyAttack(Player* player) override;

    friend std::istream& operator>>(std::istream& in, Potato& obj);
};



#endif //GARDENINGSIMULATOR_POTATO_H
