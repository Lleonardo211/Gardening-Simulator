#include "Plot.h"
#include "Plant.h"
#include "Potato.h"
#include "Tomato.h"
#include <iostream>
#include <random>

int Plot::plotCnt = 0;
int Plot::rainLevel = 0;
int Plot::sunlightLevel = 0;

Plot::Plot() : id(plotCnt++), plant(nullptr), waterLevel(rainLevel), fertilization(0), radioactivity(0) {}

Plot::~Plot() {
    if (plant!=nullptr) {
        delete plant;
        plant = nullptr;
    }
}

std::ostream& operator<<(std::ostream& out, const Plot& obj) {
    out << "Plot #" << obj.id + 1 << '\n';
    if (obj.plant == nullptr)
        out << "Empty\n";
    else
        out << *obj.plant << '\n';
    return out;
}

void Plot::calculateWeather() {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> distribution(1,300);

    rainLevel = distribution(gen);
    sunlightLevel = distribution(gen);
}

void Plot::assignPlant(int seedType) {
    switch (seedType) {
        case 1: {
            Plant* p = new Potato;
            this -> plant = p;
            break;

        }
        case 2: {
            Plant* t = new Tomato;
            this -> plant = t;
            break;
        }
    }
}

void Plot::removePlant() {
    if (plant != nullptr) {
        delete plant;
        plant = nullptr;
    } else {
        std::cout << "This plot is already empty!\n";
        std::cin.get();
    }
}

int Plot::increaseWaterLevel(int addition) {
    if (waterLevel + addition <= 300) {
        waterLevel += addition;
        return 0;
    } else {
        int aux = waterLevel;
        waterLevel = 300;
        aux = aux + addition - 300;
        return aux;
    }
}

bool Plot::empty() {
    if (this -> plant == nullptr)
        return 1;
    return 0;
}
