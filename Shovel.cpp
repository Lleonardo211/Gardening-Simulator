#include "Shovel.h"
#include <iostream>

Shovel::Shovel() : type(1), AP(5), durability(30){}

Shovel::Shovel(int type, int AP, int durability)
    : type(type), AP(AP), durability(durability) {}

Shovel::Shovel(const Shovel& obj)
    : type(obj.type), AP(obj.AP), durability(obj.durability) {}

Shovel& Shovel::operator=(const Shovel& obj) {
    if (this != &obj) {
        type = obj.type;
        AP = obj.AP;
        durability = obj.durability;
    }
    return *this;
}

void Shovel::mediumUpgrade() {
    type = 2;
    AP = 10;
    durability = 50;
}

void Shovel::bigUpgrade() {
    type = 3;
    AP = 20;
    durability = 100;
}

std::istream& operator>>(std::istream& in, Shovel& obj) {
    std::cout << "Choose type: ";
    in >> obj.type;
    in.ignore();
    std::cout << "\nChoose AP: ";
    in >> obj.AP;
    in.ignore();
    std::cout << "\nChoose type durability: ";
    in >> obj.durability;
    in.ignore();
    return in;
}

std::ostream& operator<<(std::ostream& out, const Shovel& obj) {
    switch (obj.type) {
        case 2: {
            out << "reinforced shovel " << obj.AP << "AP";
            break;
        }
        case 3: {
            out << "combat shovel "<< obj.AP << "AP";
            break;
        }
        default: {
            out << "old shovel "<< obj.AP << "AP";
            break;
        }
    }
    return out;
}


