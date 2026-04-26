#ifndef GARDENINGSIMULATOR_TOMATO_H
#define GARDENINGSIMULATOR_TOMATO_H

#include "Plant.h"
#include <string>

class Tomato : public Plant {
public:
    Tomato() : Plant(false, 40, 5, 4) {}
    ~Tomato() override;

    std::string plantType() const override;
    void plantAttack(Player *player) override;
    void lightAttack(Player* player) override;
    void normalAttack(Player* player) override;
    void heavyAttack(Player* player) override;
};



#endif //GARDENINGSIMULATOR_TOMATO_H
