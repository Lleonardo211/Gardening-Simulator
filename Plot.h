#ifndef GARDENINGSIMULATOR_PLOT_H
#define GARDENINGSIMULATOR_PLOT_H

#include <iostream>

class Plant;

class Plot {
private:
    static int plotCnt;
    const int id;
    static int rainLevel;
    static int sunlightLevel;
    int waterLevel;
    bool fertilization;
    bool radioactivity;
    Plant* plant;

public:
    Plot();
    ~Plot();

    static void calculateWeather();
    void assignPlant(int seedType);
    void removePlant();
    int increaseWaterLevel(int addition);
    void increaseFertilization() { fertilization = 1; }
    void increaseRadioactivity() { radioactivity = 1; }
    bool empty();

    int getWaterLevel() { return waterLevel; }
    int getSunlightLevel() { return sunlightLevel; }
    int getFertilization() { return fertilization; }

    friend std::ostream& operator<<(std::ostream& out, const Plot& obj);

};



#endif //GARDENINGSIMULATOR_PLOT_H
