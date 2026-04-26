#include "Tomato.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <random>

Tomato::~Tomato() {}

std::string Tomato::plantType() const { return "tomato"; }

void Tomato::plantAttack(Player* player) {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(1,100);
    int luck = dist(gen);
    if (luck < 33 ) {
        lightAttack(player);
    } else if (luck <66) {
        normalAttack(player);
    } else {
        heavyAttack(player);
    }
}

void Tomato::lightAttack(Player* player) {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(1,100);
    int luck = dist(gen);
    if (luck > 40) {
        int damage = AP;
        player -> takeDamage(damage);
        std::cout << "Plant hit for " << damage << " damage!";
        std::cin.get();
    } else {
        std::cout << "Plant missed!";
        std::cin.get();
    }
}

void Tomato::normalAttack(Player* player) {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(1,100);
    int luck = dist(gen);
    if (luck > 60) {
        int damage = AP * 2;
        player -> takeDamage(damage);
        std::cout << "Plant hit for " << damage << " damage!";
        std::cin.get();
    } else {
        std::cout << "Plant missed!";
        std::cin.get();
    }
}

void Tomato::heavyAttack(Player* player) {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(1,100);
    int luck = dist(gen);
    if (luck > 75) {
        int damage = AP * 3;
        player -> takeDamage(damage);
        std::cout << "Plant hit for "<< damage << " damage!";
        std::cin.get();
    } else {
        std::cout << "Plant missed!";
        std::cin.get();
    }
}
