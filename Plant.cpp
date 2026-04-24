#include "Plant.h"
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Plant& obj) {
    out << obj.plantType();
    return out;
}