#ifndef SPACE_INVADERS_OBJECT_STRUCTURE_H
#define SPACE_INVADERS_OBJECT_STRUCTURE_H

#include <stdint.h>

typedef struct {
    int width;
    int height;
    int scale;
    uint16_t *bits;
    int pos_x;
    int pos_y;

} object_desc_t;

typedef struct {
    int count;
    object_desc_t *objects;

} objects_t;

#endif //SPACE_INVADERS_OBJECT_STRUCTURE_H
