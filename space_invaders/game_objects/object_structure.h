#ifndef SPACE_INVADERS_OBJECT_STRUCTURE_H
#define SPACE_INVADERS_OBJECT_STRUCTURE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int bit_width;
    int bit_height;
    int scale;
    uint32_t *bits;
    int bits_offset;
    int status;
    int pos_x;
    int pos_y;
    int size_x;
    int size_y;
    int cost;


} object_desc_t;

typedef struct {
    int count;
    object_desc_t *objects;
    int speed_x;
    int speed_y;

    int curr_obj_idx;
    uint16_t color;

} objects_t;

#endif //SPACE_INVADERS_OBJECT_STRUCTURE_H
