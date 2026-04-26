#include "Shovel.h"
#include <iostream>

Shovel::Shovel() : type(1), AP(10), durability(30){}

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

void Shovel::mediumUpgrade() {
    type = 2;
    AP = 20;
    durability = 50;
}

void Shovel::bigUpgrade() {
    type = 3;
    AP = 30;
    durability = 100;
}


