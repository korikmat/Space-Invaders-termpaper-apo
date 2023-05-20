#ifndef SPACE_INVADERS_VIEW_H
#define SPACE_INVADERS_VIEW_H

#include "game_objects/object_structure.h"

#define PURPLE  0b1001100000010100
#define BLACK   0b0000000000000000
#define WHITE   0b1111111111111111
#define RED     0b1111100000000000
#define GREEN   0b0000011111100000
#define BLUE    0b0000000000011111
#define ORANGE  0b1111110010100000
#define PINK    0b1111100000011000
#define BROWN   0b0110000000000000
#define GRAY    0b0101101011101011


void init_drawing();
void render(objects_t** objects, int obj_num);

#endif //SPACE_INVADERS_VIEW_H
