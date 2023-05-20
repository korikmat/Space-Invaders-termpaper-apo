#include <stdlib.h>
#include "game_text.h"

#include "object_structure.h"
#include "textures/font_texture.h"


#define CHAR_NUM 10000

object_desc_t* game_text_desc;

objects_t* create_game_text(){
    game_text_desc = malloc(CHAR_NUM*sizeof(object_desc_t));

    for(int i = 0; i < CHAR_NUM; i++){
        game_text_desc[i].status = false;
        game_text_desc[i].scale = 2;
        game_text_desc[i].bits = char_bits;
        game_text_desc[i].bit_height = *char_height;
        game_text_desc[i].bit_width = char_width[0];
        game_text_desc[i].size_y = game_text_desc[i].bit_height * game_text_desc[i].scale;
    }
    objects_t* game_text = malloc(sizeof(objects_t));
    game_text->count = CHAR_NUM;
    game_text->objects = game_text_desc;
    game_text->curr_obj_idx = 0;

    return game_text;
}

