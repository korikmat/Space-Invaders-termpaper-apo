#include <stdlib.h>
#include <stdio.h>

#include "lives.h"
#include "../textures/space_ship_texture.h"

#define ERROR 101

#define POS_X 30
#define POS_Y 300
#define DISTANCE_X 35



objects_t* create_lives(){
    object_desc_t* live_desc = malloc(GAME_LIVES * sizeof(object_desc_t));
    if(live_desc == NULL){
        fprintf(stderr, "ERROR: Cant allocate mem for live_desc!\n");
        exit(ERROR);
    }

    for(int i = 0; i < GAME_LIVES; i++){
        live_desc[i].bit_width = space_ship_width;
        live_desc[i].bit_height = space_ship_height;
        live_desc[i].scale = 2;
        live_desc[i].bits = space_ship_bits;
        live_desc[i].pos_x = POS_X + DISTANCE_X*i;
        live_desc[i].pos_y = POS_Y;
        live_desc[i].size_x = live_desc->bit_width * live_desc->scale;
        live_desc[i].size_y = live_desc->bit_height * live_desc->scale;
        live_desc[i].status = false;
        live_desc[i].bits_offset = 0;
    }

    objects_t *lives = malloc(sizeof(objects_t));
    if(lives == NULL){
        fprintf(stderr, "ERROR: Cant allocate mem for lives!\n");
        exit(ERROR);
    }
    lives->count = GAME_LIVES;

    lives->objects = live_desc;

    printf("Lives was created successfully!\n");
    return lives;
}

void reset_lives(objects_t* lives){
    object_desc_t* live_desc = lives->objects;

    for(int i = 0; i < GAME_LIVES; i++){
        live_desc[i].bit_width = space_ship_width;
        live_desc[i].bit_height = space_ship_height;
        live_desc[i].scale = 2;
        live_desc[i].bits = space_ship_bits;
        live_desc[i].pos_x = POS_X + DISTANCE_X*i;
        live_desc[i].pos_y = POS_Y;
        live_desc[i].size_x = live_desc->bit_width * live_desc->scale;
        live_desc[i].size_y = live_desc->bit_height * live_desc->scale;
        live_desc[i].status = true;
        live_desc[i].bits_offset = 0;
    }

    lives->count = GAME_LIVES;

    lives->objects = live_desc;


}