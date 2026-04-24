#ifndef GARDENINGSIMULATOR_TOMATO_H
#define GARDENINGSIMULATOR_TOMATO_H

#include "Plant.h"
#include "Player.h"
#include <string>

class Tomato : public Plant {
public:
    Tomato();
    ~Tomato() override;

    std::string plantType() const override;
    void lightAttack(Player* player) override;
    void normalAttack(Player* player) override;
    void heavyAttack(Player* player) override;
};



#endif //GARDENINGSIMULATOR_TOMATO_H
