#include "Store.h"
#include <iostream>
#include <algorithm>
#include <random>

Store::Store()
    : knowledge(false),
      ragebait(0),
      potatoPrice(40),
      tomatoPrice(35),
      shovelPrice(500),
      tankPrice(600),
      medkitPrice(20),
      fertilizerPrice(30),
      atomicFerPrice(80),
      plotPrice(1000),
      potatoPayment(30),
      tomatoPayment(25){}

Store::Store(bool knowledge,
             int ragebait,
             int potatoPrice,
             int tomatoPrice,
             int shovelPrice,
             int tankPrice,
             int medkitPrice,
             int fertilizerPrice,
             int atomicFerPrice,
             int plotPrice,
             int potatoPayment,
             int tomatoPayment)
                 :
             knowledge(knowledge),
             ragebait(ragebait),
             potatoPrice(potatoPrice),
             tomatoPrice(tomatoPrice),
             shovelPrice(shovelPrice),
             tankPrice(tankPrice),
             medkitPrice(medkitPrice),
             fertilizerPrice(fertilizerPrice),
             atomicFerPrice(atomicFerPrice),
             plotPrice(plotPrice),
             potatoPayment(potatoPayment),
             tomatoPayment(tomatoPayment){}


Store::Store(const Store& obj)
    : knowledge(obj.knowledge),
      ragebait(obj.ragebait),
      potatoPrice(obj.potatoPrice),
      tomatoPrice(obj.tomatoPrice),
      shovelPrice(obj.shovelPrice),
      tankPrice(obj.tankPrice),
      medkitPrice(obj.medkitPrice),
      fertilizerPrice(obj.fertilizerPrice),
      atomicFerPrice(obj.atomicFerPrice),
      plotPrice(obj.plotPrice),
      potatoPayment(obj.potatoPayment),
      tomatoPayment(obj.tomatoPayment){}

Store& Store::operator=(const Store& obj) {
    if (this != &obj) {
        knowledge = obj.knowledge;
        ragebait = obj.ragebait;
        potatoPrice = obj.potatoPrice;
        tomatoPrice = obj.tomatoPrice;
        shovelPrice = obj.shovelPrice;
        tankPrice = obj.tankPrice;
        medkitPrice = obj.medkitPrice;
        fertilizerPrice = obj.fertilizerPrice;
        atomicFerPrice = obj.atomicFerPrice;
        plotPrice = obj.plotPrice;
        potatoPayment = obj.potatoPayment;
        tomatoPayment = obj.tomatoPayment;
    }
    return *this;
}

int Store::barter(int coins, int price) const {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(30, 100);

    double ratio = static_cast<double>(coins) / price;
    int chance =  static_cast<int>(ratio * 100);
    chance = std::clamp(chance, 1, 85);
    if (dist(gen) > chance) return -1;
    return static_cast<int>(price * (1.0 - ratio * 0.5));
}

void Store::increaseRagebait(int coins, int price) {
    double ratio = static_cast<double>(coins) / price;
    int rageIncrease = static_cast<int>((1.0 - ratio) * 10);
    ragebait += rageIncrease;
}

bool Store::ragebaitCheck() const {
    if (ragebait >= 10) return true;
    return false;
}

void Store::resetPrices() {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(-15,15);
    potatoPrice = std::max(10, potatoPrice + dist(gen));
    tomatoPrice = std::max(10, tomatoPrice + dist(gen));
    medkitPrice = std::max(10, medkitPrice + dist(gen));
    fertilizerPrice = std::max(10, fertilizerPrice + dist(gen));
    atomicFerPrice = std::max(10, atomicFerPrice + dist(gen));
    potatoPayment = std::max(10, potatoPayment + dist(gen));
    tomatoPayment = std::max(10, tomatoPayment + dist(gen));
}

std::istream& operator>>(std::istream& in, Store& obj) {
    std::cout << "\nPotato seed price: ";
    in >> obj.potatoPrice;
    in.ignore();
    std::cout <<"\nTomato seed price: ";
    in >> obj.tomatoPrice;
    in.ignore();
    std::cout << "\nShovel price: ";
    in >> obj.shovelPrice;
    in.ignore();
    std::cout << "\nTank price: ";
    in >> obj.tankPrice;
    in.ignore();
    std::cout << "\nMedkit price: ";
    in >> obj.medkitPrice;
    in.ignore();
    std::cout << "\nFertilizer prize: ";
    in >> obj.fertilizerPrice;
    in.ignore();
    std::cout << "\nAtomic Fertilizer prize: ";
    in >> obj.atomicFerPrice;
    in.ignore();
    std::cout << "\nPlot prize: ";
    in >> obj.plotPrice;
    in.ignore();
    return in;
}

std::ostream& operator<<(std::ostream& out, const Store& obj) {
    std::cout << "\nPotato seed price: ";
    out << obj.potatoPrice;
    std::cout << "\nTomato seed price: ";
    out << obj.tomatoPrice;
    std::cout << "\nShovel price: ";
    out << obj.shovelPrice;
    std::cout << "\nTank price: ";
    out << obj.tankPrice;
    std::cout << "\nMedkit price: ";
    out << obj.medkitPrice;
    std::cout << "\nFertilizer prize: ";
    out << obj.fertilizerPrice;
    std::cout << "\nAtomic Fertilizer prize: ";
    out << obj.atomicFerPrice;
    std::cout << "\nPlot prize: ";
    out << obj.plotPrice;
    return out;
}
