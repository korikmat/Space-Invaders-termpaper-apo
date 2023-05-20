#ifndef SPACE_INVADERS_FONT_TEXTURE_H
#define SPACE_INVADERS_FONT_TEXTURE_H

#include "stdint.h"

static uint16_t char_bits[] = {
/* Number 0:
   ht=8, width=7
   +-------+
   |  ***  |
   | *   * |
   | *  ** |
   | * * * |
   | **  * |
   | *   * |
   |  ***  |
   +-------+ */
            0x0,
        0x1c,
        0x22,
        0x26,
        0x2a,
        0x32,
        0x22,
        0x1c,

/* Number 1 :
   ht=8, width=5
   +-----+
   |  *  |
   | **  |
   |  *  |
   |  *  |
   |  *  |
   |  *  |
   | *** |
   +-----+ */
            0x0,
        0x4,
        0xc,
        0x4,
        0x4,
        0x4,
        0x4,
        0xe,

/*   Number 2:
   ht=8, width=7
   +-------+
   |  ***  |
   | *   * |
   |     * |
   |   **  |
   |  *    |
   | *     |
   | ***** |
   +-------+ */
            0x0,
        0x1c,
        0x22,
        0x2,
        0xc,
        0x10,
        0x20,
        0x3e,

/* Number 3  :
   ht=8, width=7
   +-------+
   |  ***  |
   | *   * |
   |     * |
   |   **  |
   |     * |
   | *   * |
   |  ***  |
   +-------+ */
            0x0,
        0x1c,
        0x22,
        0x2,
        0xc,
        0x2,
        0x22,
        0x1c,

/* Number 4:
   ht=8, width=7
   +-------+
   |    ** |
   |   * * |
   |  *  * |
   | *   * |
   | ***** |
   |     * |
   |     * |
   +-------+ */
            0x0,
        0x6,
        0xa,
        0x12,
        0x22,
        0x3e,
        0x2,
        0x2,

/* Number 5:
   ht=8, width=7
   +-------+
   | ***** |
   | *     |
   | ****  |
   |     * |
   |     * |
   | *   * |
   |  ***  |
   +-------+ */
            0x0,
        0x3e,
        0x20,
        0x3c,
        0x2,
        0x2,
        0x22,
        0x1c,


/* Number 6:
   ht=8, width=7
   +-------+
   |  ***  |
   | *   * |
   | *     |
   | ****  |
   | *   * |
   | *   * |
   |  ***  |
   +-------+ */
            0x0,
        0x1c,
        0x22,
        0x20,
        0x3c,
        0x22,
        0x22,
        0x1c,

/* Number 7:
   ht=8, width=7
   +-------+
   | ***** |
   |     * |
   |    *  |
   |   *   |
   |  *    |
   |  *    |
   |  *    |
   +-------+ */
            0x0,
        0x3e,
        0x2,
        0x4,
        0x8,
        0x10,
        0x10,
        0x10,

/* Number 8:
   ht=8, width=7
   +-------+
   |  ***  |
   | *   * |
   | *   * |
   |  ***  |
   | *   * |
   | *   * |
   |  ***  |
   +-------+ */
            0x0,
        0x1c,
        0x22,
        0x22,
        0x1c,
        0x22,
        0x22,
        0x1c,

/* Number 9:
   ht=8, width=7
   +-------+
   |  ***  |
   | *   * |
   | *   * |
   |  **** |
   |     * |
   | *   * |
   |  ***  |
   +-------+ */
            0x0,
        0x1c,
        0x22,
        0x22,
        0x1e,
        0x2,
        0x22,
        0x1c,


};

static uint8_t char_height[] = {
        8,
};

static uint8_t char_width[] = {
        7,
        5,
        7,
        7,
        7,
        7,
        7,
        7,
        7,
        7,

};

#endif //SPACE_INVADERS_FONT_TEXTURE_H
