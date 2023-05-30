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
/* UFO  :
   ht=7, width=16
   +----------------+
   |     ******     |
   |   **********   |
   |  ************  |
   | ** ** ** ** ** |
   |****************|
   |  ***  **  ***  |
   |   *        *   |
   +----------------+ */
0x7e0,
0x1ff8,
0x3ffc,
0x6db6,
0xffff,
0x399c,
0x1008,

/* UFO_BROKEN :
   ht=8, width=20
   +--------------------+
   |  *  * *      * *  *|
   |   *        **    * |
   |* *   *****  **     |
   |     *******  ***   |
   |    *** * * *  ***  |
   |  *   *****   **    |
   |*      * *   **     |
   |  *   *   *    *    |
   +--------------------+ */
0x25029,
0x100c2,
0xa3e60,
0x7f38,
0xea9c,
0x23e30,
0x81460,
0x22210,        
};

static uint8_t space_ship_width = 15;
static uint8_t space_ship_height = 8;

#endif //SPACE_INVADERS_SPACE_SHIP_TEXTURE_H
