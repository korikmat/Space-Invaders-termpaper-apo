#ifndef SPACE_INVADERS_WALL_PIECES_TEXTURE_H
#define SPACE_INVADERS_WALL_PIECES_TEXTURE_H

#include <stdint.h>

static uint32_t wall_pieces_bits[] = {
///* BLOCK_0:
//   ht=5, width=5
//  +-----+
//  |     |
//  |     |
//  |     |
//  |     |
//  |     |
//  +-----+ */
//        0x0,
//        0x0,
//        0x0,
//        0x0,
//        0x0,



/* BLOCK_4 cond_1 :
   ht=5, width=5
  +-----+
  |    *|
  |   **|
  |  ***|
  | ****|
  |*****|
  +-----+ */
        0x1,
        0x3,
        0x7,
        0xf,
        0x1f,

/* BLOCK_4 cond_2 :
   ht=5, width=5
  +-----+
  |     |
  |   **|
  |   **|
  | ** *|
  |* ***|
  +-----+ */
        0x0,
        0x3,
        0x3,
        0xd,
        0x17,

/* BLOCK_4 cond_3 :
   ht=5, width=5
  +-----+
  |     |
  |   * |
  |   **|
  | **  |
  |  * *|
  +-----+ */
        0x0,
        0x2,
        0x3,
        0xc,
        0x5,

/* BLOCK_4 cond_4 :
   ht=5, width=5
  +-----+
  |     |
  |     |
  |   **|
  |     |
  |  * *|
  +-----+ */
        0x0,
        0x0,
        0x2,
        0x0,
        0x5,




/* BLOCK_1 cond_1:
   ht=5, width=5
  +-----+
  |*****|
  |*****|
  |*****|
  |*****|
  |*****|
  +-----+ */
        0x1f,
        0x1f,
        0x1f,
        0x1f,
        0x1f,

/* BLOCK_1 cond_2:
   ht=5, width=5
  +-----+
  |*  **|
  |**** |
  | ** *|
  | |
  |*** *|
  +-----+ */
        0x13,
        0x1e,
        0xd,
        0x1b,
        0x1d,

/* BLOCK_1 cond_3:
   ht=5, width=5
  +-----+
  |   * |
  |*  **|
  | **  |
  |*  * |
  |* * *|
  +-----+ */
        0x2,
        0x13,
        0xc,
        0x12,
        0x15,

/* BLOCK_1 cond_4:
   ht=5, width=5
  +-----+
  |     |
  |*   *|
  |  *  |
  |   * |
  |*    |
  +-----+ */
        0x0,
        0x11,
        0x4,
        0x2,
        0x10,



/* BLOCK_5 cond_1:
   ht=5, width=5
  +-----+
  |*    |
  |**   |
  |***  |
  |**** |
  |*****|
  +-----+ */
        0x10,
        0x18,
        0x1c,
        0x1e,
        0x1f,

/* BLOCK_5 cond_2:
   ht=5, width=5
  +-----+
  |     |
  |**   |
  |**   |
  |* ** |
  |*** *|
  +-----+ */
        0x0,
        0x18,
        0x18,
        0x16,
        0x1d,

/* BLOCK_5 cond_3:
   ht=5, width=5
  +-----+
  |     |
  | *   |
  |**   |
  |  ** |
  |* *  |
  +-----+ */
        0x0,
        0x8,
        0x18,
        0x6,
        0x14,

/* BLOCK_5 cond_4:
   ht=5, width=5
  +-----+
  |     |
  |     |
  |**   |
  |     |
  |* *  |
  +-----+ */
        0x0,
        0x0,
        0x18,
        0x0,
        0x14,



/* BLOCK_2 cond_1:
   ht=5, width=5
  +-----+
  |*****|
  |**** |
  |***  |
  |**   |
  |*    |
  +-----+ */
        0x1f,
        0x1e,
        0x1c,
        0x18,
        0x10,

/* BLOCK_2 cond_2:
   ht=5, width=5
  +-----+
  |*** *|
  |**** |
  |* *  |
  |**   |
  |*    |
  +-----+ */
        0x1d,
        0x1e,
        0x14,
        0x18,
        0x0,

/* BLOCK_2 cond_3:
   ht=5, width=5
  +-----+
  |* *  |
  |  ** |
  |**   |
  | *   |
  |     |
  +-----+ */
        0x14,
        0x6,
        0x18,
        0x8,
        0x0,

/* BLOCK_2 cond_4:
   ht=5, width=5
  +-----+
  |* *  |
  |     |
  |**   |
  |     |
  |     |
  +-----+ */
        0x14,
        0x0,
        0x18,
        0x0,
        0x0,


/* BLOCK_3 cond_1:
   ht=5, width=5
  +-----+
  |*****|
  | ****|
  |  ***|
  |   **|
  |    *|
  +-----+ */
        0x1f,
        0xf,
        0x7,
        0x3,
        0x1,

/* BLOCK_3 cond_2:
   ht=5, width=5
  +-----+
  |* ***|
  | ** *|
  |  ***|
  |   **|
  |     |
  +-----+ */
        0x17,
        0xd,
        0x3,
        0x3,
        0x0,

/* BLOCK_3 cond_3:
   ht=5, width=5
  +-----+
  |  * *|
  | **  |
  |   **|
  |   * |
  |     |
  +-----+ */
        0x5,
        0xc,
        0x3,
        0x2,
        0x0,

/* BLOCK_3 cond_4:
   ht=5, width=5
  +-----+
  |  * *|
  |     |
  |   **|
  |     |
  |     |
  +-----+ */
        0x5,
        0x0,
        0x3,
        0x0,
        0x0,





};

static uint8_t wall_pieces_width = 5;
static uint8_t wall_pieces_height = 5;

#endif //SPACE_INVADERS_WALL_PIECES_TEXTURE_H
