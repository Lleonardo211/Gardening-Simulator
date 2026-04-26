#include "Plant.h"
#include <iostream>

Plant::Plant() : growth(false) {}

Plant::Plant(bool growth, int hp, int ap, int toughness)
    :  growth(growth), HP(hp), AP(ap), toughness(toughness) {}

void Plant::takeDamage(int damage) {
    HP -= damage;
    if (HP < 0) HP = 0;
}

std::ostream& operator<<(std::ostream& out, const Plant& obj) {
    out << obj.plantType();
    return out;
}