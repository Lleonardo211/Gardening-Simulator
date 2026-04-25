#include "Plant.h"
#include <iostream>

Plant::Plant() : growth(false) {}

std::ostream& operator<<(std::ostream& out, const Plant& obj) {
    out << obj.plantType();
    return out;
}