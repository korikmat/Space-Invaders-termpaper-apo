#include <stdlib.h>
#include <stdio.h>

#include "view.h"
#include "kit_tools/mzapo_phys.h"
#include "kit_tools/mzapo_regs.h"
#include "kit_tools/mzapo_parlcd.h"

#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 320


void draw_background_to_array(uint16_t color);
void draw_objects_to_array(object_desc_t *objects, int count, uint16_t color);
void draw_pixel_scaled(int x, int y, int scale, uint16_t color);
void draw_array_to_display();


unsigned char *parlcd_mem_base;
uint16_t *display;

void init_drawing(){
    display = malloc(480*320*2);

    parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    parlcd_hx8357_init(parlcd_mem_base);
}

void render(objects_t** objects, int obj_num){

    draw_background_to_array(BLACK);

    for(int i = 0; i < obj_num; i++){
        draw_objects_to_array(objects[i]->objects, objects[i]->count, objects[i]->color);
    }

    draw_array_to_display();
}

void draw_background_to_array(uint16_t color){
    for (int i = 0; i < DISPLAY_WIDTH*DISPLAY_HEIGHT; i++) {
        display[i]=color;
    }
}
void draw_objects_to_array(object_desc_t *objects, int count, uint16_t color){
    object_desc_t* object;
    for(int ptr = 0; ptr < count; ptr++){
        object = objects+ptr;
        if(!object->status){
            continue;
        }
        for(int i = 0; i < object->bit_height; i++){
            for(int j = 0; j < object->bit_width; j++){
                if((object->bits+object->bits_offset)[i]<<j & (0x1<<(object->bit_width - 1))){
                    draw_pixel_scaled(object->pos_x+j*object->scale, object->pos_y+i*object->scale, object->scale, color);
                }
            }
        }
    }
}

void draw_pixel_scaled(int x, int y, int scale, uint16_t color){
    for(int i = 0; i < scale; i++){
        for(int j = 0; j < scale; j++){
            display[(x+j)%DISPLAY_WIDTH + (y+i)*DISPLAY_WIDTH] = color;
        }
    }
}

void draw_array_to_display(){
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (int ptr = 0; ptr < DISPLAY_WIDTH*DISPLAY_HEIGHT; ptr++) {
        parlcd_write_data(parlcd_mem_base, display[ptr]);
    }
}