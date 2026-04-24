#include "Tank.h"

Tank::Tank()
    : size(2000),
      waterVolume(2000) {}

void Tank::mediumUpgrade() {
    size = 3000;
}
void Tank::bigUpgrade() {
    size = 4000;
}
