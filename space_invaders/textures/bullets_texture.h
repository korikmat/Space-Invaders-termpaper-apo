#ifndef SPACE_INVADERS_BULLETS_TEXTURE_H
#define SPACE_INVADERS_BULLETS_TEXTURE_H

#include "stdint.h"

static uint16_t bullets_bits[] = {
/* MY_BULLET   ():
   ht=4, width=1
   +-+
   |*|
   |*|
   |*|
   |*|
   +-+ */
0x1,
0x1,
0x1,
0x1,

/* BULLET_1 cond_1  :
   ht=7, width=3
   +---+
   | * |
   |  *|
   | * |
   |*  |
   | * |
   |  *|
   | * |
   +---+ */
0x2,
0x1,
0x2,
0x4,
0x2,
0x1,
0x2,

/* BULLET_1 cond_2  :
   ht=7, width=3
   +---+
   |  *|
   | * |
   |*  |
   | * |
   |  *|
   | * |
   |*  |
   +---+ */
0x1,
0x2,
0x4,
0x2,
0x1,
0x2,
0x4,

/* BULLET_1 cond_3  :
   ht=7, width=3
   +---+
   | * |
   |*  |
   | * |
   |  *|
   | * |
   |*  |
   | * |
   +---+ */
0x2,
0x4,
0x2,
0x1,
0x2,
0x4,
0x2,



/* BULLET_1 cond_4  :
   ht=7, width=3
   +---+
   |*  |
   | * |
   |  *|
   | * |
   |*  |
   | * |
   |  *|
   +---+ */
0x4,
0x2,
0x1,
0x2,
0x4,
0x2,
0x1,

/* BULLET_2 cond_1  :
   ht=7, width=3
   +---+
   | * |
   | * |
   | * |
   | * |
   |***|
   | * |
   | * |
   +---+ */
0x2,
0x2,
0x2,
0x2,
0x7,
0x2,
0x2,

/* BULLET_2 cond_2  :
   ht=7, width=3
   +---+
   | * |
   | * |
   |***|
   | * |
   | * |
   | * |
   | * |
   +---+ */
0x2,
0x2,
0x7,
0x2,
0x2,
0x2,
0x2,

/* BULLET_2 cond_3  :
   ht=7, width=3
   +---+
   |***|
   | * |
   | * |
   | * |
   | * |
   | * |
   | * |
   +---+ */
0x7,
0x2,
0x2,
0x2,
0x2,
0x2,
0x2,

/* BULLET_2 cond_4  :
   ht=7, width=3
   +---+
   | * |
   | * |
   | * |
   | * |
   | * |
   | * |
   |***|
   +---+ */
0x2,
0x2,
0x2,
0x2,
0x2,
0x2,
0x7,

/* BULLET_3 cond_1  :
   ht=7, width=3
   +---+
   | * |
   | * |
   |** |
   | **|
   | * |
   |** |
   | **|
   +---+ */
0x2,
0x2,
0x6,
0x3,
0x2,
0x6,
0x3,

/* BULLET_3 cond_2  :
   ht=7, width=2
   +--+
   | *|
   | *|
   | *|
   | *|
   | *|
   | *|
   | *|
   +--+ */
0x1,
0x1,
0x1,
0x1,
0x1,
0x1,
0x1,

/* BULLET_3 cond_3  :
   ht=7, width=3
   +---+
   | **|
   |** |
   | * |
   | **|
   |** |
   | * |
   | * |
   +---+ */
0x3,
0x6,
0x2,
0x3,
0x6,
0x2,
0x2,
};

#endif //SPACE_INVADERS_BULLETS_TEXTURE_H
