#include <stdlib.h>
#include <stdio.h>

#include "space_ship.h"
#include "../textures/space_ship_texture.h"

#define ERROR 101

#define START_POS 250
#define POS_Y 276



objects_t* create_space_ship(){
    object_desc_t* space_ship_desc = malloc(1 * sizeof(object_desc_t));
    if(space_ship_desc == NULL){
        fprintf(stderr, "ERROR: Cant allocate mem for space_ship_desc!\n");
        exit(ERROR);
    }

    space_ship_desc->bit_width = space_ship_width;
    space_ship_desc->bit_height = space_ship_height;
    space_ship_desc->scale = 2;
    space_ship_desc->bits = space_ship_bits;
    space_ship_desc->pos_x = START_POS;
    space_ship_desc->pos_y = POS_Y;
    space_ship_desc->size_x = space_ship_desc->bit_width * space_ship_desc->scale;
    space_ship_desc->size_y = space_ship_desc->bit_height * space_ship_desc->scale;
    space_ship_desc->status = false;
    space_ship_desc->bits_offset = 0;


    objects_t *space_ship = malloc(sizeof(objects_t));
    if(space_ship == NULL){
        fprintf(stderr, "ERROR: Cant allocate mem for space_ship!\n");
        exit(ERROR);
    }
    space_ship->count = 1;

    space_ship->objects = space_ship_desc;
//    objects_t space_ship = {
//            1,
//            live_desc
//    };
    printf("Spaceship was created successfully!\n");
    return space_ship;
}

void reset_space_ship(objects_t* space_ship){
    object_desc_t* space_ship_desc = space_ship->objects;

    space_ship_desc->bit_width = space_ship_width;
    space_ship_desc->bit_height = space_ship_height;
    space_ship_desc->scale = 2;
    space_ship_desc->bits = space_ship_bits;
    space_ship_desc->pos_x = START_POS;
    space_ship_desc->pos_y = POS_Y;
    space_ship_desc->size_x = space_ship_desc->bit_width * space_ship_desc->scale;
    space_ship_desc->size_y = space_ship_desc->bit_height * space_ship_desc->scale;
    space_ship_desc->status = true;
    space_ship_desc->bits_offset = 0;

    space_ship->count = 1;

    space_ship->objects = space_ship_desc;
}

void move_space_ship(object_desc_t* space_ship, int pos_x){
//    int pos_x = get_pos_x_from_knob();
//    printf("%d\n", pos_x);
    space_ship->pos_x = pos_x;

}