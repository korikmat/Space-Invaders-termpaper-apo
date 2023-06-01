#include <stdlib.h>
#include <stdio.h>

#include "view.h"
#include "kit_tools/mzapo_phys.h"
#include "kit_tools/mzapo_regs.h"
#include "kit_tools/mzapo_parlcd.h"
#include "background_pink_floyd.h"

#define ERROR 101

#define EXIT (-2)
#define MENU (-1)
#define WIN 0
#define GAME 1

#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 320
#define MENU_BACKGROUND_NAME "menu-background.ppm"
#define GAME_BACKGROUND_NAME "game-background.ppm"

void init_background(uint16_t *background, char* filename);

void draw_background_to_array(int game_state);
void draw_objects_to_array(object_desc_t *objects, int count, uint16_t color);
void draw_pixel_scaled(int x, int y, int scale, uint16_t color);
void draw_array_to_display();


unsigned char *parlcd_mem_base;
uint16_t display[DISPLAY_WIDTH*DISPLAY_HEIGHT];
uint16_t menu_background[DISPLAY_WIDTH*DISPLAY_HEIGHT];
uint16_t game_background[DISPLAY_WIDTH*DISPLAY_HEIGHT];


void init_drawing(){

    init_background(menu_background, MENU_BACKGROUND_NAME);
    init_background(game_background, GAME_BACKGROUND_NAME);

    parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    parlcd_hx8357_init(parlcd_mem_base);
}

void init_background(uint16_t *background, char* filename){
    FILE* background_file = fopen(filename, "rb");
    if(background_file == NULL){
        fprintf(stderr, "ERROR: Cant open background file!\n");
        exit(ERROR);
    }

    char ppm_type[2];
    int width, height, depth;

    if(fscanf(background_file, "%2c %d %d %d ", ppm_type, &width, &height, &depth) != 4){
        fprintf(stderr, "ERROR: Cant read header of background file!\n");
        exit(ERROR);
    }
    unsigned char background_ppm[width*height*3];
    if(fread(background_ppm, width*3, height, background_file) != height){
        fprintf(stderr, "ERROR: Cant read background file!\n");
        exit(ERROR);
    }
    fclose(background_file);
    printf("%d %d\n", width, height);
    for(int i = 0; i < width*height; i++){
        background[i] = (uint16_t)(background_ppm[i*3]*31/255);
        background[i] = background[i]<<6;
        background[i] = background[i] | (uint16_t)(background_ppm[i*3+1]*63/255);
        background[i] = background[i]<<5;
        background[i] = background[i] | (uint16_t)(background_ppm[i*3+2]*31/255);
    }

}

void render(objects_t** objects, int obj_num, int game_state){

    draw_background_to_array(game_state);

    for(int i = 0; i < obj_num; i++){
        draw_objects_to_array(objects[i]->objects, objects[i]->count, objects[i]->color);
    }

    draw_array_to_display();
}

void draw_background_to_array(int game_state){
    uint16_t *background;
    switch (game_state) {
        case MENU:
            background = menu_background;
            break;
        case GAME:
            background = game_background;
            break;
        default:
            fprintf(stderr, "ERROR: Unknown game state while drawing background!\n");
            exit(1);
    }
    for (int i = 0; i < DISPLAY_WIDTH*DISPLAY_HEIGHT; i++) {
        display[i]=background[i];
    }

}
void draw_objects_to_array(object_desc_t *objects, int count, uint16_t color){
    object_desc_t* object;
    for(int ptr = 0; ptr < count; ptr++){
        object = objects+ptr;
        if(object->status == false){
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