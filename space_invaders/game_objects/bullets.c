#include <stdlib.h>
#include <stdio.h>

#include "object_structure.h"
#include "bullets.h"
#include "textures/bullets_texture.h"

void move_alien_bullet(object_desc_t* bullet);

objects_t* create_bullets(){

    object_desc_t* bullets_desc = malloc(BULLETS_NUM*sizeof(object_desc_t));

    for(int i = 0; i < BULLETS_NUM; i++){
        bullets_desc[i].bit_height = 4;
        bullets_desc[i].bit_width = 1;

        if(i == 0){
//            bullets_desc[i].bits = bullets_bits;
            bullets_desc[i].bits_offset = 0;
        } else {
            bullets_desc[i].bits_offset = 1*4;
            bullets_desc[i].bit_height = 7;
            bullets_desc[i].bit_width = 3;
//            bullets_desc[i].bits = bullets_bits;
        }

        bullets_desc[i].pos_x = 0;
        bullets_desc[i].pos_y = 0;
        bullets_desc[i].scale = 2;
        bullets_desc[i].size_x = bullets_desc[i].bit_width * bullets_desc[i].scale;
        bullets_desc[i].size_y = bullets_desc[i].bit_height * bullets_desc[i].scale;
        bullets_desc[i].status = false;
        bullets_desc[i].bits = bullets_bits;
//        bullets_desc[0].bits_offset = 0;

    }

    objects_t* bullets = malloc(sizeof(objects_t));
    bullets->count = BULLETS_NUM;
    bullets->curr_obj_idx = 0;
    bullets->objects = bullets_desc;

    return bullets;
}

void move_space_ship_bullet(object_desc_t* bullet, int pos_x, bool red_knob_pressed){
    if(!bullet->status && red_knob_pressed){
        bullet->status = true;
        bullet->pos_x = pos_x;
        bullet->pos_y = 276;
        printf("KNOB WAS PRESSED\n");
    }
    if(!bullet->status){
        return;
    }
    if(bullet->pos_y-8 <= 0){
        bullet->status = false;
        return;
    }
//    uint32_t b = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
//    uint32_t r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

//    printf("%d\n", (int)(((r>>16)&0xff)*320)/256);
//    printf("%d\n", (int)((b&0xff)*480)/256);

//    bullet->pos_y = (int)(((r>>16)&0xff)*320)/256;
//    bullet->pos_x = (int)((b&0xff)*480)/256;
    bullet->pos_y-=8;
}

void try_to_attack_space_ship(objects_t* bullets, objects_t* aliens){
    for(int i = 0; i < aliens->count; i++){
        object_desc_t alien = aliens->objects[i];
        object_desc_t* bullet = bullets->objects+i+1;
        if(alien.status > 0){
            if(!bullet->status && random()%1000+1 == 1){

                bullet->status = true;
                bullet->pos_x = alien.pos_x+alien.size_x/2;
                bullet->pos_y = alien.pos_y+alien.size_y;

            }
        }
        if(bullet->status){
            move_alien_bullet(bullet);
        }
    }
}

void move_alien_bullet(object_desc_t* bullet){
    if(bullet->pos_y+bullet->size_y+4 > 320){
        bullet->status = false;
        return;
    }
    bullet->pos_y+=4;
}
