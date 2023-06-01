#include <stdlib.h>

#include "object_structure.h"
#include "walls.h"
#include "textures/wall_pieces_texture.h"



objects_t* create_walls(){

    object_desc_t* wall_pieces_desc = malloc(WALLS_NUM*WALL_PIECES_NUM*sizeof(object_desc_t));

    for(int i = 0; i < WALLS_NUM; i++){
        for(int j = WALL_PIECES_NUM*i; j < WALLS_NUM*WALL_PIECES_NUM; j++){

//            wall_pieces_desc[j].status = 4;
            wall_pieces_desc[j].status = false;

            wall_pieces_desc[j].bit_width = wall_pieces_width;
            wall_pieces_desc[j].bit_height = wall_pieces_height;
            wall_pieces_desc[j].scale = 2;
            wall_pieces_desc[j].size_x = wall_pieces_desc[j].bit_width*wall_pieces_desc[j].scale;
            wall_pieces_desc[j].size_y = wall_pieces_desc[j].bit_height*wall_pieces_desc[j].scale;
            wall_pieces_desc[j].bits = wall_pieces_bits;
            wall_pieces_desc[j].bits_offset = 0;

        }

        int pos_x = WALLS_OFFSET_X + WALLS_DISTANCE_X*i;
        int pos_y = WALLS_OFFSET_Y;

        wall_pieces_desc[0+WALL_PIECES_NUM*i].pos_x = pos_x;
        wall_pieces_desc[0+WALL_PIECES_NUM*i].pos_y = pos_y;
        wall_pieces_desc[0+WALL_PIECES_NUM*i].bits = wall_pieces_bits;
        // wall_pieces_desc[0+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*0)*4;


        wall_pieces_desc[1+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[1+WALL_PIECES_NUM*i].size_x*1;
        wall_pieces_desc[1+WALL_PIECES_NUM*i].pos_y = pos_y;
       wall_pieces_desc[1+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*1)*4;
        // wall_pieces_desc[1+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*1)*4;


        wall_pieces_desc[2+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[2+WALL_PIECES_NUM*i].size_x*2;
        wall_pieces_desc[2+WALL_PIECES_NUM*i].pos_y = pos_y;
       wall_pieces_desc[2+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*1)*4;
        // wall_pieces_desc[2+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*1)*4;


        wall_pieces_desc[3+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[3+WALL_PIECES_NUM*i].size_x*3;
        wall_pieces_desc[3+WALL_PIECES_NUM*i].pos_y = pos_y;
       wall_pieces_desc[3+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*2)*4;
        // wall_pieces_desc[3+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*2)*4;


        wall_pieces_desc[4+WALL_PIECES_NUM*i].pos_x = pos_x;
        wall_pieces_desc[4+WALL_PIECES_NUM*i].pos_y = pos_y+wall_pieces_desc[4+WALL_PIECES_NUM*i].size_y*1;
       wall_pieces_desc[4+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*1)*4;
        // wall_pieces_desc[4+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*1)*4;


        wall_pieces_desc[5+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[5+WALL_PIECES_NUM*i].size_x*1;
        wall_pieces_desc[5+WALL_PIECES_NUM*i].pos_y = pos_y+wall_pieces_desc[5+WALL_PIECES_NUM*i].size_y*1;
       wall_pieces_desc[5+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*3)*4;
        // wall_pieces_desc[5+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*3)*4;


        wall_pieces_desc[6+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[6+WALL_PIECES_NUM*i].size_x*2;
        wall_pieces_desc[6+WALL_PIECES_NUM*i].pos_y = pos_y+wall_pieces_desc[6+WALL_PIECES_NUM*i].size_y*1;
       wall_pieces_desc[6+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*4)*4;
        // wall_pieces_desc[6+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*4)*4;

        wall_pieces_desc[7+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[7+WALL_PIECES_NUM*i].size_x*3;
        wall_pieces_desc[7+WALL_PIECES_NUM*i].pos_y = pos_y+wall_pieces_desc[7+WALL_PIECES_NUM*i].size_y*1;
       wall_pieces_desc[7+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*1)*4;
        // wall_pieces_desc[7+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*1)*4;


        wall_pieces_desc[8+WALL_PIECES_NUM*i].pos_x = pos_x;
        wall_pieces_desc[8+WALL_PIECES_NUM*i].pos_y = pos_y+wall_pieces_desc[8+WALL_PIECES_NUM*i].size_y*2;
       wall_pieces_desc[8+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*1)*4;
        // wall_pieces_desc[8+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*1)*4;


        wall_pieces_desc[9+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[9+WALL_PIECES_NUM*i].size_x*3;
        wall_pieces_desc[9+WALL_PIECES_NUM*i].pos_y = pos_y+wall_pieces_desc[9+WALL_PIECES_NUM*i].size_y*2;
       wall_pieces_desc[9+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*1)*4;
        // wall_pieces_desc[9+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*1)*4;

    }
    objects_t* walls = malloc(sizeof(objects_t));
    walls->count = WALLS_NUM*WALL_PIECES_NUM;
    walls->curr_obj_idx = 0;
    walls->objects = wall_pieces_desc;

    return walls;
}

void reset_walls(objects_t* walls){

    object_desc_t* wall_pieces_desc = walls->objects;

    for(int i = 0; i < WALLS_NUM; i++){
        for(int j = WALL_PIECES_NUM*i; j < WALLS_NUM*WALL_PIECES_NUM; j++){

            wall_pieces_desc[j].status = 4;

            wall_pieces_desc[j].bit_width = wall_pieces_width;
            wall_pieces_desc[j].bit_height = wall_pieces_height;
            wall_pieces_desc[j].scale = 2;
            wall_pieces_desc[j].size_x = wall_pieces_desc[j].bit_width*wall_pieces_desc[j].scale;
            wall_pieces_desc[j].size_y = wall_pieces_desc[j].bit_height*wall_pieces_desc[j].scale;
            wall_pieces_desc[j].bits = wall_pieces_bits;
            wall_pieces_desc[j].bits_offset = 0;

        }

        int pos_x = WALLS_OFFSET_X + WALLS_DISTANCE_X*i;
        int pos_y = WALLS_OFFSET_Y;

        wall_pieces_desc[0+WALL_PIECES_NUM*i].pos_x = pos_x;
        wall_pieces_desc[0+WALL_PIECES_NUM*i].pos_y = pos_y;
        wall_pieces_desc[0+WALL_PIECES_NUM*i].bits = wall_pieces_bits;
        // wall_pieces_desc[0+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*0)*4;


        wall_pieces_desc[1+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[1+WALL_PIECES_NUM*i].size_x*1;
        wall_pieces_desc[1+WALL_PIECES_NUM*i].pos_y = pos_y;
        wall_pieces_desc[1+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*1)*4;
        // wall_pieces_desc[1+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*1)*4;


        wall_pieces_desc[2+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[2+WALL_PIECES_NUM*i].size_x*2;
        wall_pieces_desc[2+WALL_PIECES_NUM*i].pos_y = pos_y;
        wall_pieces_desc[2+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*1)*4;
        // wall_pieces_desc[2+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*1)*4;


        wall_pieces_desc[3+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[3+WALL_PIECES_NUM*i].size_x*3;
        wall_pieces_desc[3+WALL_PIECES_NUM*i].pos_y = pos_y;
        wall_pieces_desc[3+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*2)*4;
        // wall_pieces_desc[3+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*2)*4;


        wall_pieces_desc[4+WALL_PIECES_NUM*i].pos_x = pos_x;
        wall_pieces_desc[4+WALL_PIECES_NUM*i].pos_y = pos_y+wall_pieces_desc[4+WALL_PIECES_NUM*i].size_y*1;
        wall_pieces_desc[4+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*1)*4;
        // wall_pieces_desc[4+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*1)*4;


        wall_pieces_desc[5+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[5+WALL_PIECES_NUM*i].size_x*1;
        wall_pieces_desc[5+WALL_PIECES_NUM*i].pos_y = pos_y+wall_pieces_desc[5+WALL_PIECES_NUM*i].size_y*1;
        wall_pieces_desc[5+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*3)*4;
        // wall_pieces_desc[5+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*3)*4;


        wall_pieces_desc[6+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[6+WALL_PIECES_NUM*i].size_x*2;
        wall_pieces_desc[6+WALL_PIECES_NUM*i].pos_y = pos_y+wall_pieces_desc[6+WALL_PIECES_NUM*i].size_y*1;
        wall_pieces_desc[6+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*4)*4;
        // wall_pieces_desc[6+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*4)*4;

        wall_pieces_desc[7+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[7+WALL_PIECES_NUM*i].size_x*3;
        wall_pieces_desc[7+WALL_PIECES_NUM*i].pos_y = pos_y+wall_pieces_desc[7+WALL_PIECES_NUM*i].size_y*1;
        wall_pieces_desc[7+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*1)*4;
        // wall_pieces_desc[7+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*1)*4;


        wall_pieces_desc[8+WALL_PIECES_NUM*i].pos_x = pos_x;
        wall_pieces_desc[8+WALL_PIECES_NUM*i].pos_y = pos_y+wall_pieces_desc[8+WALL_PIECES_NUM*i].size_y*2;
        wall_pieces_desc[8+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*1)*4;
        // wall_pieces_desc[8+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*1)*4;


        wall_pieces_desc[9+WALL_PIECES_NUM*i].pos_x = pos_x+wall_pieces_desc[9+WALL_PIECES_NUM*i].size_x*3;
        wall_pieces_desc[9+WALL_PIECES_NUM*i].pos_y = pos_y+wall_pieces_desc[9+WALL_PIECES_NUM*i].size_y*2;
        wall_pieces_desc[9+WALL_PIECES_NUM*i].bits = wall_pieces_bits+(wall_pieces_height*1)*4;
        // wall_pieces_desc[9+WALL_PIECES_NUM*i].bits_offset = (wall_pieces_height*1)*4;

    }
    walls->count = WALLS_NUM*WALL_PIECES_NUM;
    walls->curr_obj_idx = 0;
    walls->objects = wall_pieces_desc;
}
