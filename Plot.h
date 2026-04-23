#ifndef GARDENINGSIMULATOR_PLOT_H
#define GARDENINGSIMULATOR_PLOT_H

#include "Plant.h"
#include <iostream>

class Plot {
private:
    static int plotCnt;
    const int id;
    static int rainLevel;
    static int sunlightLevel;
    Plant* plant;

public:
    Plot();
    ~Plot();

    static void calculateWeather();
    void assignPlant(Plant* plant);
    void removePlant();

    friend std::ostream& operator<<(std::ostream& out, const Plot& obj);

};



#endif //GARDENINGSIMULATOR_PLOT_H
