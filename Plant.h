#ifndef GARDENINGSIMULATOR_PLANT_H
#define GARDENINGSIMULATOR_PLANT_H

#include <string>

class Player;

class Plant {
protected:
    bool growth;
    int HP;
    int AP;
    int toughness;

public:
    Plant();
    Plant(bool growth, int hp, int ap, int toughness);
    Plant(const Plant& obj);
    Plant& operator=(const Plant& obj);
    virtual ~Plant() {};

    virtual std::string plantType() const = 0;
    virtual void plantAttack(Player* player) = 0;
    virtual void lightAttack(Player* player) = 0;
    virtual void normalAttack(Player* player) = 0;
    virtual void heavyAttack(Player* player) = 0;
    void takeDamage(int damage);

    bool getGrowth() const { return growth; }
    int getHP() const { return HP; }
    int getAP() const { return AP; }
    int getToughness() const { return toughness; }

    void setGrowth(bool newGrowth) { growth = newGrowth; }
    void setHP(int newHP) { HP = newHP; }
    void setAP(int newAP) { AP = newAP; }
    void setToughness(int newToughness) { toughness = newToughness; }

    friend std::ostream& operator<<(std::ostream& out, const Plant& obj);

};



#endif //GARDENINGSIMULATOR_PLANT_H
