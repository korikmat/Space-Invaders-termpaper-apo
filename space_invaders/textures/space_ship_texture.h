#ifndef SPACE_INVADERS_SPACE_SHIP_TEXTURE_H
#define SPACE_INVADERS_SPACE_SHIP_TEXTURE_H

#include <stdint.h>

static uint16_t space_ship_bits[] = {

/* Spaceship ():
   ht=8, width=15
   +---------------+
   |       *       |
   |      ***      |
   |      ***      |
   | ************* |
   |***************|
   |***************|
   |***************|
   |***************|
   +---------------+ */
        0x80,
        0x1c0,
        0x1c0,
        0x3ffe,
        0x7fff,
        0x7fff,
        0x7fff,
        0x7fff,
};

static uint8_t space_ship_width = 15;
static uint8_t space_ship_height = 8;

#endif //SPACE_INVADERS_SPACE_SHIP_TEXTURE_H
