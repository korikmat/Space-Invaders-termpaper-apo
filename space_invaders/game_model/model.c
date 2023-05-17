#include "model.h"
#include "kit_tools/mzapo_phys.h"
#include "kit_tools/mzapo_regs.h"
#include <stdio.h>

void move_space_ship(object_desc_t* space_ship);
int get_pos_x_from_knob();
void move_aliens(objects_t * aliens);

unsigned char *mem_base;

void init_model(){
    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
}

void advance_state(objects_t* aliens, objects_t* space_ship){
    move_space_ship(space_ship->objects);
    move_aliens(aliens);

}

void move_space_ship(object_desc_t* space_ship){
    int pos_x = get_pos_x_from_knob();
//    printf("%d\n", pos_x);
    space_ship->pos_x = pos_x;
}

int get_pos_x_from_knob(){
    uint32_t r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    return (int)((r&0xff)*480)/256;
}

void move_aliens(objects_t* aliens){

    object_desc_t *alien = aliens->objects;
    int* speed_x = &aliens->speed_x;
    int* speed_y = &aliens->speed_y;

    for(int i = 0; i < aliens->count; i++){

        if(alien[i].pos_x+alien[i].size_x+(*speed_x) > 480 || alien[i].pos_x+(*speed_x) < 0){
            (*speed_y) = 30;
            (*speed_x)*=-1;
        }
        if(alien[i].pos_y+alien[i].size_y+(*speed_y) > 320){
            return;
        }

    }
    for(int i = 0; i < aliens->count; i++){
        alien[i].pos_x+=(*speed_x);
        alien[i].pos_y+=(*speed_y);
    }
    (*speed_y) = 0;
}
