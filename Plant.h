#ifndef GARDENINGSIMULATOR_PLANT_H
#define GARDENINGSIMULATOR_PLANT_H

#include <string>

class Player;

class Plant {
protected:
    int HP;
    int AP;
    int toughness;

public:
    Plant() {};
    virtual ~Plant() {};

    virtual std::string plantType() const = 0;
    virtual void lightAttack(Player* player) = 0;
    virtual void normalAttack(Player* player) = 0;
    virtual void heavyAttack(Player* player) = 0;

    friend std::ostream& operator<<(std::ostream& out, const Plant& obj);

};



#endif //GARDENINGSIMULATOR_PLANT_H
