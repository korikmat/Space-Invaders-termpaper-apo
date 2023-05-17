#include "model.h"
#include "kit_tools/mzapo_phys.h"
#include "kit_tools/mzapo_regs.h"

void move_space_ship(object_desc_t space_ship);
int get_pos_x_from_knob();
void move_alien(object_desc_t alien);

unsigned char *mem_base;

void init_model(){
    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
}

void advance_state(objects_t* aliens, objects_t* space_ship){
    move_space_ship(space_ship->objects[0]);

    for(int i = 0; i < aliens->count; i++){
        move_alien(aliens->objects[i]);
    }
}

void move_space_ship(object_desc_t space_ship){
    int pos_x = get_pos_x_from_knob();

    space_ship.pos_x = pos_x;
}

int get_pos_x_from_knob(){
    uint32_t r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    return (int)((r&0xff)*480)/256;
}

void move_alien(object_desc_t alien){
    alien.pos_x += 1;
}