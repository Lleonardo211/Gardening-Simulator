#ifndef GARDENINGSIMULATOR_TANK_H
#define GARDENINGSIMULATOR_TANK_H

#include <iostream>

class Tank {
private:
    int size;
    int waterVolume;
public:
    Tank();
    ~Tank() {}
    void mediumUpgrade();
    void bigUpgrade();

    int getWaterVolume() const { return waterVolume; }
    void setWaterVolume(int newVolume) { waterVolume = newVolume; }

    friend std::ostream& operator<<(std::ostream& out, const Tank& obj);
};



#endif //GARDENINGSIMULATOR_TANK_H
