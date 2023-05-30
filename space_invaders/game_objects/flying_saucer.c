#include <stdlib.h>

#include "flying_saucer.h"
#include "../textures/flying_saucer_texture.h"

#define FLYING_SAUCER_POS_X 0
#define FLYING_SAUCER_POS_Y 30

object_desc_t* flying_saucer_desc;

objects_t* create_flying_saucer(){
    flying_saucer_desc = malloc(1 * sizeof(object_desc_t));

    flying_saucer_desc->bit_width = flying_saucer_width;
    flying_saucer_desc->bit_height = flying_saucer_height;
    flying_saucer_desc->scale = 2;
    flying_saucer_desc->bits = flying_saucer_bits;
    flying_saucer_desc->pos_x = FLYING_SAUCER_POS_X;
    flying_saucer_desc->pos_y = FLYING_SAUCER_POS_Y;
    flying_saucer_desc->size_x = flying_saucer_desc->bit_width * flying_saucer_desc->scale;
    flying_saucer_desc->size_y = flying_saucer_desc->bit_height * flying_saucer_desc->scale;
    flying_saucer_desc->status = false;
    flying_saucer_desc->bits_offset = 0;

    objects_t *flying_saucer = malloc(sizeof(objects_t));
    flying_saucer->count = 1;

    flying_saucer->objects = flying_saucer_desc;
    flying_saucer->speed_x = 1;
//    objects_t space_ship = {
//            1,
//            live_desc
//    };

    return flying_saucer;
}
