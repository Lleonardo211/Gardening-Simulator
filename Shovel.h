#ifndef GARDENINGSIMULATOR_SHOVEL_H
#define GARDENINGSIMULATOR_SHOVEL_H

#include <iostream>

class Shovel {
private:
    int AP;
    int durability;

public:
    Shovel(int type);
    ~Shovel() = default;

    friend std::ostream& operator<<(std::ostream& out, const Shovel& obj);

};



#endif //GARDENINGSIMULATOR_SHOVEL_H
