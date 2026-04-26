#include "Tomato.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <random>

Tomato::Tomato(const Tomato& obj) : Plant(obj.growth, obj.HP, obj.AP, obj.toughness){}

Tomato& Tomato::operator=(const Tomato& obj) {
    if (this != &obj) {
        growth = obj.growth;
        HP = obj.HP;
        AP = obj.AP;
        toughness = obj.toughness;
    }
    return *this;
}

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
    std::cout << "The " << plantType() << " is attacking!!\n";
    std::cin.get();
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(1,100);
    int luck = dist(gen);
    if (luck > 40) {
        int damage = AP;
        player -> takeDamage(damage);
        std::cout << "Plant hit for "<< damage << " damage!\n";
        std::cin.get();
    } else {
        std::cout << "IT MISSED!\n";
        std::cin.get();
    }
}

void Tomato::normalAttack(Player* player) {
    std::cout << "The " << plantType() << " is attacking!!\n";
    std::cin.get();
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(1,100);
    int luck = dist(gen);
    if (luck > 60) {
        int damage = AP * 2;
        player -> takeDamage(damage);
        std::cout << "Plant hit for "<< damage << " damage!\n";
        std::cin.get();
    } else {
        std::cout << "IT MISSED!\n";
        std::cin.get();
    }
}

void Tomato::heavyAttack(Player* player) {
    std::cout << "The " << plantType() << " is preparing a massive attack!!\n";
    std::cin.get();
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(1,100);
    int luck = dist(gen);
    if (luck > 75) {
        int damage = AP * 3;
        player -> takeDamage(damage);
        std::cout << "Plant hit for "<< damage << " damage!\n";
        std::cin.get();
    } else {
        std::cout << "IT MISSED!\n";
        std::cin.get();
    }
}

std::istream& operator>>(std::istream& in, Tomato& obj) {
    std::cout << "Choose HP: ";
    in >> obj.HP;
    in.ignore();
    std::cout << "\nChoose AP: ";
    in >> obj.AP;
    in.ignore();
    std::cout << "\nChoose toughness: ";
    in >> obj.toughness;
    in.ignore();
    return in;
}
