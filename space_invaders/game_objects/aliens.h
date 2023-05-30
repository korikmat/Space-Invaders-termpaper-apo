#ifndef SPACE_INVADERS_ALIENS_H
#define SPACE_INVADERS_ALIENS_H


#include "object_structure.h"

#define ALIENS_NUM 55
#define ALIENS_IN_LINE 11

#define ALIENS_INITIAL_SPEED_X 4
#define ALIENS_INITIAL_SPEED_Y 0

#define FIRST_LINE 0
#define SECOND_LINE 1
#define THIRD_LINE 2
#define FOURTH_LINE 3
#define FIFTH_LINE 4

#define FIRST 1
#define SECOND 4
#define THIRD 7


#define OFFSET_Y 68
#define DISTANCE_X 32
#define DISTANCE_Y 24

#define FIRST_GROUP_OFFSET_X 74

#define SECOND_GROUP_OFFSET_X 70

#define THIRD_GROUP_OFFSET_X 68

#define FIRST_GROUP_ALIENS_COST 30
#define SECOND_GROUP_ALIENS_COST 20
#define THIRD_GROUP_ALIENS_COST 10


objects_t* create_aliens();

void reset_aliens(objects_t* aliens);

#endif //SPACE_INVADERS_ALIENS_H
