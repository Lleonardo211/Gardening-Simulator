#include "Tank.h"
#include <iostream>

Tank::Tank()
    : size(2000),
      waterVolume(2000) {}

std::ostream& operator<<(std::ostream& out, const Tank& obj) {
    switch (obj.size) {
        case 3000: {
            out << "medium water-tank";
        }
        case 4000: {
            out << "large water-tank";
        }
        default: {
            out << "small water-tank";
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