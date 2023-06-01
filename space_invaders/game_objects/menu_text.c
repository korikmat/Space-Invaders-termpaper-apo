#include <stdlib.h>
#include <stdio.h>

#include "menu_text.h"
#include "object_structure.h"
#include "textures/font_texture.h"

#define ERROR 101

#define CHAR_NUM 100

object_desc_t* menu_text_desc;

objects_t* create_menu_text(){
    menu_text_desc = malloc(CHAR_NUM*sizeof(object_desc_t));
    if(menu_text_desc == NULL){
        fprintf(stderr, "ERROR: Cant allocate mem for menu_text_desc!\n");
        exit(ERROR);
    }

    for(int i = 0; i < CHAR_NUM; i++){
        menu_text_desc[i].status = false;
        menu_text_desc[i].scale = 2;
        menu_text_desc[i].bits = char_bits;
        menu_text_desc[i].bit_height = *char_height;
        menu_text_desc[i].bit_width = char_width[0];
        menu_text_desc[i].size_y = menu_text_desc[i].bit_height * menu_text_desc[i].scale;
        menu_text_desc[i].bits_offset = 0;
    }
    objects_t* menu_text = malloc(sizeof(objects_t));
    if(menu_text == NULL){
        fprintf(stderr, "ERROR: Cant allocate mem for menu_text!\n");
        exit(ERROR);
    }
    menu_text->count = CHAR_NUM;
    menu_text->objects = menu_text_desc;
    menu_text->curr_obj_idx = 0;

    printf("Menu text was created successfully!\n");
    return menu_text;
}
