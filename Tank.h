#ifndef GARDENINGSIMULATOR_TANK_H
#define GARDENINGSIMULATOR_TANK_H



class Tank {
private:
    int size;
    int waterVolume;
public:
    Tank();
    ~Tank() {}
    void mediumUpgrade();
    void bigUpgrade();

    int getWaterVolume() { return waterVolume; }
};



#endif //GARDENINGSIMULATOR_TANK_H
