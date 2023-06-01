#ifndef SPACE_INVADERS_WALLS_H
#define SPACE_INVADERS_WALLS_H

#include "object_structure.h"

#define WALLS_NUM 4
#define WALL_PIECES_NUM 10

#define WALLS_OFFSET_X 92
#define WALLS_OFFSET_Y 238

#define WALLS_DISTANCE_X 85

objects_t* create_walls();
void reset_walls(objects_t* walls);


#endif //SPACE_INVADERS_WALLS_H
