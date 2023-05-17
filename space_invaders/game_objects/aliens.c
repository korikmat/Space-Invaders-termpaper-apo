#include <stdlib.h>

#include "aliens.h"
#include "../textures/aliens_texture.h"
#include "object_structure.h"

#define ALIENS_NUM 55
#define ALIENS_IN_LINE 11

#define ALIENS_INITIAL_SPEED_X 1
#define ALIENS_INITIAL_SPEED_Y 0

#define FIRST_LINE 0
#define SECOND_LINE 1
#define THIRD_LINE 2
#define FOURTH_LINE 3
#define FIFTH_LINE 4

#define FIRST 0
#define SECOND 1
#define THIRD 2


#define OFFSET_Y 63
#define DISTANCE_X 29
#define DISTANCE_Y 24

#define FIRST_GROUP_OFFSET_X 87

#define SECOND_GROUP_OFFSET_X 84

#define THIRD_GROUP_OFFSET_X 83

object_desc_t *aliens_desc;

objects_t* create_aliens(){
    aliens_desc = malloc(ALIENS_NUM * sizeof(object_desc_t));
    for(int i = 0; i < ALIENS_NUM; i++){
        switch (i/ALIENS_IN_LINE) {
            case FIRST_LINE:
                aliens_desc[i].height = aliens_height[FIRST];
                aliens_desc[i].width = aliens_width[FIRST];

                aliens_desc[i].bits=aliens_bits;

                aliens_desc[i].pos_x = FIRST_GROUP_OFFSET_X + DISTANCE_X * (i % ALIENS_IN_LINE);
                aliens_desc[i].pos_y = OFFSET_Y + DISTANCE_Y * (i / ALIENS_IN_LINE);

                break;
            case SECOND_LINE:
            case THIRD_LINE:
                aliens_desc[i].height = aliens_height[SECOND];
                aliens_desc[i].width = aliens_width[SECOND];

                aliens_desc[i].bits= aliens_bits + aliens_height[FIRST];

                aliens_desc[i].pos_x = SECOND_GROUP_OFFSET_X + DISTANCE_X * (i % ALIENS_IN_LINE);
                aliens_desc[i].pos_y = OFFSET_Y + DISTANCE_Y * (i / ALIENS_IN_LINE);
                break;
            case FOURTH_LINE:
            case FIFTH_LINE:
                aliens_desc[i].height = aliens_height[THIRD];
                aliens_desc[i].width = aliens_width[THIRD];

                aliens_desc[i].bits= aliens_bits + aliens_height[FIRST] + aliens_height[SECOND];

                aliens_desc[i].pos_x = THIRD_GROUP_OFFSET_X + DISTANCE_X * (i % ALIENS_IN_LINE);
                aliens_desc[i].pos_y = OFFSET_Y + DISTANCE_Y * (i / ALIENS_IN_LINE);
                break;
        }
        aliens_desc[i].scale = 2;
        aliens_desc[i].size_x = aliens_desc[i].width*aliens_desc[i].scale;
        aliens_desc[i].size_y = aliens_desc[i].height*aliens_desc[i].scale;


    }

    objects_t *aliens = malloc(sizeof(objects_t));
    aliens->count = ALIENS_NUM;
    aliens->objects = aliens_desc;
    aliens->speed_x = ALIENS_INITIAL_SPEED_X;
    aliens->speed_y = ALIENS_INITIAL_SPEED_Y;

//    objects_t aliens = {
//            ALIENS_NUM,
//            aliens_desc,
//    };

    return aliens;
}
