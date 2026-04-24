#ifndef GARDENINGSIMULATOR_POTATO_H
#define GARDENINGSIMULATOR_POTATO_H


#include "Plant.h"
#include <string>

class Player;

class Potato : public Plant {
public:
    Potato();
    ~Potato() override;

    std::string plantType() const override;
    void lightAttack(Player* player) override;
    void normalAttack(Player* player) override;
    void heavyAttack(Player* player) override;
};



#endif //GARDENINGSIMULATOR_POTATO_H
