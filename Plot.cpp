#include "Plot.h"
#include <random>

int Plot::plotCnt = 0;
int Plot::rainLevel = 0;
int Plot::sunlightLevel = 0;

Plot::Plot() : id(plotCnt++) {
    plant = nullptr;
}

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
        out << *obj.plant;
    return out;
}

void Plot::calculateWeather() {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> distr(1,10);

    rainLevel = distr(gen);
    sunlightLevel = distr(gen);
}

void Plot::assignPlant(Plant* plant) {
    if (this -> plant != nullptr)
        delete this -> plant;
    this -> plant = plant;
}

void Plot::removePlant() {
    if (plant != nullptr) {
        delete plant;
        plant = nullptr;
    }
}