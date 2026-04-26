#ifndef GARDENINGSIMULATOR_TANK_H
#define GARDENINGSIMULATOR_TANK_H

#include <iostream>

class Tank {
private:
    int size;
    int waterVolume;
public:
    Tank();
    Tank(int size, int waterVolume);
    Tank(const Tank& obj);
    Tank& operator=(const Tank& obj);
    ~Tank() = default;

    void mediumUpgrade();
    void bigUpgrade();

    int getSize() const { return size; }
    int getWaterVolume() const { return waterVolume; }

    void setSize(int newSize) { size = newSize; }
    void setWaterVolume(int newVolume) { waterVolume = newVolume; }

    friend std::istream& operator>>(std::istream& in, Tank& obj);
    friend std::ostream& operator<<(std::ostream& out, const Tank& obj);
};



#endif //GARDENINGSIMULATOR_TANK_H
