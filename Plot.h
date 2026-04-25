#ifndef GARDENINGSIMULATOR_PLOT_H
#define GARDENINGSIMULATOR_PLOT_H

#include <iostream>
#include <string>

#include "Plant.h"

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
    void increaseFertilization() { fertilization = true; }
    void increaseRadioactivity() { radioactivity = true; }
    void printPlant() const;
    bool empty() const;

    static int getRainLevel() { return rainLevel; }
    static int getSunlightLevel() { return sunlightLevel; }
    int getWaterLevel() const { return waterLevel; }
    int getFertilization() const { return fertilization; }
    bool getPlantGrowth() const { return plant -> getGrowth(); }
    bool getRadioactivity() const { return radioactivity; }
    std::string getPlant() const;

    bool waterCheck() const;
    void growPlant() const;

    void setWaterLevel(int newLevel) { waterLevel = newLevel; }

    friend std::ostream& operator<<(std::ostream& out, const Plot& obj);

};



#endif //GARDENINGSIMULATOR_PLOT_H
