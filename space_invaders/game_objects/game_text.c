#include <stdlib.h>
#include <stdio.h>
#include "game_text.h"

#include "object_structure.h"
#include "textures/font_texture.h"

#define ERROR 101

#define CHAR_NUM 1000

object_desc_t* game_text_desc;

objects_t* create_game_text(){
    game_text_desc = malloc(CHAR_NUM*sizeof(object_desc_t));
    if(game_text_desc == NULL){
        fprintf(stderr, "ERROR: Cant allocate mem for game_text_desc!\n");
        exit(ERROR);
    }

    for(int i = 0; i < CHAR_NUM; i++){
        game_text_desc[i].status = false;
        game_text_desc[i].scale = 2;
        game_text_desc[i].bits = char_bits;
        game_text_desc[i].bit_height = *char_height;
        game_text_desc[i].bit_width = char_width[0];
        game_text_desc[i].size_y = game_text_desc[i].bit_height * game_text_desc[i].scale;
        game_text_desc[i].bits_offset = 0;
    }
    objects_t* game_text = malloc(sizeof(objects_t));
    if(game_text == NULL){
        fprintf(stderr, "ERROR: Cant allocate mem for game_text!\n");
        exit(ERROR);
    }
    game_text->count = CHAR_NUM;
    game_text->objects = game_text_desc;
    game_text->curr_obj_idx = 0;

    printf("Game text was created successfully!\n");
    return game_text;
}

