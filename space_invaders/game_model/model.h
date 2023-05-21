#ifndef SPACE_INVADERS_MODEL_H
#define SPACE_INVADERS_MODEL_H
#include "game_objects/object_structure.h"

#define ALIENS      0
#define SPACE_SHIP  2
#define BULLETS     1
#define WALLS       3
#define LIVES       4
#define GAME_TEXT   5

void init_model();
void advance_state(objects_t** objects, int obj_num);

#endif //SPACE_INVADERS_MODEL_H
