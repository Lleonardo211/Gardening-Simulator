#include "Tank.h"
#include <iostream>

Tank::Tank() : size(2000), waterVolume(926) {}

Tank::Tank(int size, int waterVolume) : size(size), waterVolume(waterVolume) {}

Tank::Tank(const Tank& obj) : size(obj.size), waterVolume(obj.waterVolume) {}

Tank& Tank::operator=(const Tank& obj) {
    if (this != &obj) {
        size = obj.size;
        waterVolume = obj.waterVolume;
    }
    return *this;
}

void Tank::mediumUpgrade() {
    size = 3000;
}
void Tank::bigUpgrade() {
    size = 4000;
}

std::istream& operator>>(std::istream& in, Tank& obj) {
    std::cout << "Choose size: ";
    in >> obj.size;
    in.ignore();
    std::cout << "\nChoose water volume: ";
    in >> obj.waterVolume;
    in.ignore();
    return in;
}

std::ostream& operator<<(std::ostream& out, const Tank& obj) {
    switch (obj.size) {
        case 3000: {
            out << "medium water-tank " << obj.waterVolume << '/' << obj.size;
            break;
        }
        case 4000: {
            out << "large water-tank " << obj.waterVolume << '/' << obj.size;
            break;
        }
        default: {
            out << "small water-tank " << obj.waterVolume << '/' << obj.size;
            break;
        }
    }
    return out;
}