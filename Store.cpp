#include "Store.h"
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
