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
    Shovel(int type, int AP, int durability);
    Shovel(const Shovel& obj);
    Shovel& operator=(const Shovel& obj);
    ~Shovel() = default;

    void mediumUpgrade();
    void bigUpgrade();

    int getType() const { return type; }
    int getAP() const { return AP; }
    int getDurability() const { return durability;}

    void setType(int newType) { type = newType; }
    void setAP(int newAP) { AP = newAP; }
    void setDurability(int newDurability) { durability = newDurability; }

    friend std::istream& operator>>(std::istream& in, Shovel& obj);
    friend std::ostream& operator<<(std::ostream& out, const Shovel& obj);
};



#endif //GARDENINGSIMULATOR_SHOVEL_H
