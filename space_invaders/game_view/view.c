#include <stdlib.h>

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

void render(objects_t* aliens, objects_t* space_ship){

    draw_background_to_array(PURPLE);

    draw_objects_to_array(aliens->objects, aliens->count, BLACK);
    draw_objects_to_array(space_ship->objects, space_ship->count, BLACK);

    draw_array_to_display();
}

void draw_background_to_array(uint16_t color){
    for (int i = 0; i < DISPLAY_WIDTH*DISPLAY_HEIGHT; i++) {
        display[i]=color;
    }
}
void draw_objects_to_array(object_desc_t *objects, int count, uint16_t color){
    object_desc_t object;
    for(int obj = 0; obj < count; obj++){
        object = objects[obj];
        for(int i = 0; i < object.height; i++){
            for(int j = 0; j < object.width; j++){
                if(object.bits[i]<<j & (0x1<<(object.width-1))){
                    for(int sy = 0; sy < object.scale; sy++){
                        for(int sx = 0; sx < object.scale; sx++){
                            display[object.pos_x+j*object.scale+sx + (object.height+i*object.scale+sy)*DISPLAY_WIDTH] = color;
                        }
                    }
                    draw_pixel_scaled(object.pos_x+j*object.scale, object.height+i*object.scale, object.scale, color);
                }
            }
        }
    }
}

void draw_pixel_scaled(int x, int y, int scale, uint16_t color){
    for(int i = 0; i < scale; i++){
        for(int j = 0; j < scale; j++){
            display[x+j + (y+i)*DISPLAY_WIDTH] = color;
        }
    }
}

void draw_array_to_display(){
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (int ptr = 0; ptr < DISPLAY_WIDTH*DISPLAY_HEIGHT ; ptr++) {
        parlcd_write_data(parlcd_mem_base, display[ptr]);
    }
}