#include "Tank.h"
#include <iostream>

Tank::Tank()
    : size(2000),
      waterVolume(926) {}

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

void Tank::mediumUpgrade() {
    size = 3000;
}
void Tank::bigUpgrade() {
    size = 4000;
}