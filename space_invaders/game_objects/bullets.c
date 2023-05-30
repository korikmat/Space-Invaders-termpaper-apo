#include <stdlib.h>

#include "object_structure.h"
#include "bullets.h"
#include "textures/bullets_texture.h"

object_desc_t* bullets_desc;

objects_t* create_bullets(){

    bullets_desc = malloc(BULLETS_NUM*sizeof(object_desc_t));

    for(int i = 0; i < BULLETS_NUM; i++){
        bullets_desc[i].bit_height = 4;
        bullets_desc[i].bit_width = 1;

        if(i == 0){
//            bullets_desc[i].bits = bullets_bits;
            bullets_desc[i].bits_offset = 0;
        } else {
            bullets_desc[i].bits_offset = 1*4;
            bullets_desc[i].bit_height = 7;
            bullets_desc[i].bit_width = 3;
//            bullets_desc[i].bits = bullets_bits;
        }

        bullets_desc[i].pos_x = 0;
        bullets_desc[i].pos_y = 0;
        bullets_desc[i].scale = 2;
        bullets_desc[i].size_x = bullets_desc[i].bit_width * bullets_desc[i].scale;
        bullets_desc[i].size_y = bullets_desc[i].bit_height * bullets_desc[i].scale;
        bullets_desc[i].status = false;
        bullets_desc[i].bits = bullets_bits;
//        bullets_desc[0].bits_offset = 0;

    }

    objects_t* bullets = malloc(sizeof(objects_t));
    bullets->count = BULLETS_NUM;
    bullets->curr_obj_idx = 0;
    bullets->objects = bullets_desc;

    return bullets;
}