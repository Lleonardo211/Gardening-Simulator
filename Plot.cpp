#include "Plot.h"
#include "Plant.h"
#include "Potato.h"
#include "Tomato.h"
#include <iostream>
#include <string>
#include <random>

int Plot::plotCnt = 0;
int Plot::rainLevel = 0;
int Plot::sunlightLevel = 0;

Plot::Plot() : id(plotCnt++), waterLevel(rainLevel), fertilization(false), radioactivity(false), plant(nullptr) {}

Plot::Plot(int waterLevel, bool fertilization, bool radioactivity)
    : id(plotCnt++), waterLevel(waterLevel), fertilization(fertilization), radioactivity(radioactivity), plant(nullptr) {}

Plot::Plot(const Plot& obj)
    : id(plotCnt++),
      waterLevel(obj.waterLevel),
      fertilization(obj.fertilization),
      radioactivity(obj.radioactivity),
      plant(nullptr){
    if (obj.plant != nullptr) {
        if (obj.plant -> plantType() == "potato")
            plant = new Potato(*static_cast<Potato*>(obj.plant));
        else
            plant = new Tomato(*static_cast<Tomato*>(obj.plant));
    }
}

Plot& Plot::operator=(const Plot& obj) {
    if (this != &obj) {
        waterLevel = obj.waterLevel;
        fertilization = obj.fertilization;
        radioactivity = obj.radioactivity;
        delete this -> plant;
        if (obj.plant != nullptr) {
            if (obj.plant -> plantType() == "potato")
                this -> plant = new Potato(*static_cast<Potato*>(obj.plant));
            else
                this -> plant = new Tomato(*static_cast<Tomato*>(obj.plant));
        } else {
            this -> plant = nullptr;
        }
    }
    return *this;
}

Plot::~Plot() {
    if (plant!=nullptr) {
        delete plant;
        plant = nullptr;
    }
}

void Plot::calculateWeather() {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> rainDist(1,300); //distribution
    std::uniform_int_distribution<> sunDist(1,10);

    rainLevel = rainDist(gen);
    sunlightLevel = sunDist(gen);
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
        default: {
            std::cout << "Invalid seed type!";
            std::cin.get();
        }
    }
}

std::string Plot::getPlant() const {
    if (plant == nullptr) return "none";
    return plant -> plantType();
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

void Plot::printPlant() const {
    if (plant != nullptr)
        std::cout << *plant << '\n';
    else
        std::cout << "Empty\n";
}

bool Plot::waterCheck() const {
    std::string plantType = getPlant();
    if (plantType== "potato") {
        if (waterLevel >= 150) {
            return true;
        }
    } else if (plantType == "tomato") {
        if (waterLevel >= 200) {
            return true;
        }
    }
    return false;
}

void Plot::growPlant() const {
    if (plant != nullptr && fertilization == true && waterCheck())
        plant -> setGrowth(true);
}

bool Plot::empty() const {
    if (this -> plant == nullptr)
        return true;
    return false;
}

std::istream& operator>>(std::istream& in, Plot& obj) {
    std::cout << "\nWater level: ";
    in >> obj.waterLevel;
    in.ignore();
    std::cout <<"\nFertilization: ";
    in >> obj.fertilization;
    in.ignore();
    std::cout << "\nRadioactivity: ";
    in >> obj.radioactivity;
    in.ignore();
    return in;
}

std::ostream& operator<<(std::ostream& out, const Plot& obj) {
    out << "Plot #" << obj.id + 1 << '\n';
    if (obj.plant == nullptr)
        out << "Empty\n";
    else
        out << *obj.plant << '\n';
    return out;
}