#ifndef GARDENINGSIMULATOR_TOMATO_H
#define GARDENINGSIMULATOR_TOMATO_H

#include "Plant.h"
#include <string>

class Tomato : public Plant {
public:
    Tomato() : Plant(false, 25, 5, 4) {}
    Tomato(const Tomato& obj);
    Tomato& operator=(const Tomato& obj);
    ~Tomato() override;

    std::string plantType() const override;
    void plantAttack(Player *player) override;
    void lightAttack(Player* player) override;
    void normalAttack(Player* player) override;
    void heavyAttack(Player* player) override;

    friend std::istream& operator>>(std::istream& in, Tomato& obj);
};



#endif //GARDENINGSIMULATOR_TOMATO_H
