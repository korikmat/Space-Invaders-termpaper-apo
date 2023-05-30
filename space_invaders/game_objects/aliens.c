#include <stdlib.h>

#include "aliens.h"
#include "../textures/aliens_texture.h"
#include "object_structure.h"




objects_t* create_aliens(){
    object_desc_t* aliens_desc = malloc(ALIENS_NUM * sizeof(object_desc_t));
    for(int i = 0; i < ALIENS_NUM; i++){

        switch (FIFTH_LINE-(i/ALIENS_IN_LINE)) {
            case FIRST_LINE:
                aliens_desc[i].bit_height = aliens_height[FIRST];
                aliens_desc[i].bit_width = aliens_width[FIRST];

                // aliens_desc[i].bits_offset = 1*aliens_height[ZERO];
                aliens_desc[i].bits = aliens_bits + 1*aliens_height[FIRST];



                aliens_desc[i].pos_x = FIRST_GROUP_OFFSET_X + DISTANCE_X * (i % ALIENS_IN_LINE);
                aliens_desc[i].pos_y = OFFSET_Y + DISTANCE_Y * ((ALIENS_NUM-1-i) / ALIENS_IN_LINE);

                aliens_desc[i].cost = FIRST_GROUP_ALIENS_COST;
                break;
            case SECOND_LINE:
            case THIRD_LINE:
                aliens_desc[i].bit_height = aliens_height[SECOND];
                aliens_desc[i].bit_width = aliens_width[SECOND];

                // aliens_desc[i].bits_offset = 1*aliens_height[ZERO] + 2*aliens_height[FIRST];
                aliens_desc[i].bits = aliens_bits + 3*aliens_height[FIRST] + aliens_height[SECOND];

                aliens_desc[i].pos_x = SECOND_GROUP_OFFSET_X + DISTANCE_X * (i % ALIENS_IN_LINE);
                aliens_desc[i].pos_y = OFFSET_Y + DISTANCE_Y * ((ALIENS_NUM-1-i) / ALIENS_IN_LINE);

                aliens_desc[i].cost = SECOND_GROUP_ALIENS_COST;
                break;
            case FOURTH_LINE:
            case FIFTH_LINE:
                aliens_desc[i].bit_height = aliens_height[THIRD];
                aliens_desc[i].bit_width = aliens_width[THIRD];

                // aliens_desc[i].bits_offset = 1*aliens_height[ZERO] + 2*aliens_height[FIRST] + 2*aliens_height[SECOND];
                aliens_desc[i].bits = aliens_bits + 3*aliens_height[FIRST] + 3*aliens_height[SECOND] + aliens_height[THIRD];


                aliens_desc[i].pos_x = THIRD_GROUP_OFFSET_X + DISTANCE_X * (i % ALIENS_IN_LINE);
                aliens_desc[i].pos_y = OFFSET_Y + DISTANCE_Y * ((ALIENS_NUM-1-i) / ALIENS_IN_LINE);

                aliens_desc[i].cost = THIRD_GROUP_ALIENS_COST;
                break;
        }
        aliens_desc[i].scale = 2;
        aliens_desc[i].size_x = aliens_desc[i].bit_width * aliens_desc[i].scale;
        aliens_desc[i].size_y = aliens_desc[i].bit_height * aliens_desc[i].scale;
        aliens_desc[i].status = true;
        aliens_desc[i].bits_offset = 0;
        // aliens_desc[i].bits = aliens_bits;


    }

    objects_t *aliens = malloc(sizeof(objects_t));
    aliens->count = ALIENS_NUM;
    aliens->objects = aliens_desc;
    aliens->speed_x = ALIENS_INITIAL_SPEED_X;
    aliens->speed_y = ALIENS_INITIAL_SPEED_Y;
    aliens->curr_obj_idx = 0;

//    objects_t aliens = {
//            ALIENS_NUM,
//            aliens_desc,
//    };

    return aliens;
}

void reset_aliens(objects_t* aliens){
    object_desc_t* aliens_desc = aliens->objects;
    for(int i = 0; i < aliens->count; i++){
        switch (FIFTH_LINE-(i/ALIENS_IN_LINE)) {
            case FIRST_LINE:
                aliens_desc[i].bit_height = aliens_height[FIRST];
                aliens_desc[i].bit_width = aliens_width[FIRST];

                aliens_desc[i].bits = aliens_bits + 1*aliens_height[FIRST];

                aliens_desc[i].pos_x = FIRST_GROUP_OFFSET_X + DISTANCE_X * (i % ALIENS_IN_LINE);
                aliens_desc[i].pos_y = OFFSET_Y + DISTANCE_Y * ((ALIENS_NUM-1-i) / ALIENS_IN_LINE);

                aliens_desc[i].cost = FIRST_GROUP_ALIENS_COST;
                break;
            case SECOND_LINE:
            case THIRD_LINE:
                aliens_desc[i].bit_height = aliens_height[SECOND];
                aliens_desc[i].bit_width = aliens_width[SECOND];

                aliens_desc[i].bits = aliens_bits + 3*aliens_height[FIRST] + aliens_height[SECOND];

                aliens_desc[i].pos_x = SECOND_GROUP_OFFSET_X + DISTANCE_X * (i % ALIENS_IN_LINE);
                aliens_desc[i].pos_y = OFFSET_Y + DISTANCE_Y * ((ALIENS_NUM-1-i) / ALIENS_IN_LINE);

                aliens_desc[i].cost = SECOND_GROUP_ALIENS_COST;
                break;
            case FOURTH_LINE:
            case FIFTH_LINE:
                aliens_desc[i].bit_height = aliens_height[THIRD];
                aliens_desc[i].bit_width = aliens_width[THIRD];

                aliens_desc[i].bits = aliens_bits + 3*aliens_height[FIRST] + 3*aliens_height[SECOND] + aliens_height[THIRD];

                aliens_desc[i].pos_x = THIRD_GROUP_OFFSET_X + DISTANCE_X * (i % ALIENS_IN_LINE);
                aliens_desc[i].pos_y = OFFSET_Y + DISTANCE_Y * ((ALIENS_NUM-1-i) / ALIENS_IN_LINE);

                aliens_desc[i].cost = THIRD_GROUP_ALIENS_COST;
                break;
        }
        aliens_desc[i].scale = 2;
        aliens_desc[i].size_x = aliens_desc[i].bit_width * aliens_desc[i].scale;
        aliens_desc[i].size_y = aliens_desc[i].bit_height * aliens_desc[i].scale;
        aliens_desc[i].status = true;
        aliens_desc[i].bits_offset = 0;
    }

    aliens->speed_x = ALIENS_INITIAL_SPEED_X;
    aliens->speed_y = ALIENS_INITIAL_SPEED_Y;
    aliens->curr_obj_idx = 0;
}

