#include "Shovel.h"

Shovel::Shovel(int type) {
    switch (type) {
        case 1: {
            this -> AP = 10;
            this -> durability = 30;
            break;
        }
        case 2: {
            this -> AP = 20;
            this -> durability = 50;
            break;
        }
        case 3: {
            this -> AP = 30;
            this -> durability = 100;
            break;
        }
        default: {
            this -> AP = 10;
            this -> durability = 30;
            break;
        }
    }
}
