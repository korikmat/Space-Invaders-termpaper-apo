#ifndef SPACE_INVADERS_LIVES_H
#define SPACE_INVADERS_LIVES_H

#include "object_structure.h"

#define GAME_LIVES 3

objects_t* create_lives();
void reset_lives(objects_t* lives);

#endif //SPACE_INVADERS_LIVES_H
