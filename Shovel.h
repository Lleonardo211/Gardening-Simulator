#ifndef GARDENINGSIMULATOR_SHOVEL_H
#define GARDENINGSIMULATOR_SHOVEL_H

#include <iostream>

class Shovel {
private:
    int type;
    int AP;
    int durability;

public:
    Shovel();
    ~Shovel() = default;

    void mediumUpgrade();
    void bigUpgrade();

    int getType() const { return type; }
    int getAP() const { return AP; }
    int getDurability() const { return durability;}

    friend std::ostream& operator<<(std::ostream& out, const Shovel& obj);

};



#endif //GARDENINGSIMULATOR_SHOVEL_H
