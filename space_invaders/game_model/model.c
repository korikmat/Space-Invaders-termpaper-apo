#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "kit_tools/mzapo_phys.h"
#include "kit_tools/mzapo_regs.h"
#include "textures/font_texture.h"
#include "game_objects/aliens.h"

void move_space_ship(object_desc_t* space_ship);
int get_pos_x_from_knob();

void move_alien(objects_t * aliens, int curr_idx);
int get_last_alive_alien_idx(object_desc_t* aliens, int aliens_num);

int* get_pos_x_of_objects(object_desc_t* space_ship, object_desc_t* aliens, int obj_num);
void move_bullets(objects_t* bullets, int* positions_x);
void check_knob_presses(object_desc_t* bullet, int pos_x);
void move_space_ship_bullet(object_desc_t* bullet);
void move_alien_bullet(object_desc_t* bullet);

void detect_intersections(objects_t** objects);
int detect_hits(objects_t* objects, object_desc_t* bullet);

void update_game_text(objects_t* game_text);
void write_message(objects_t* text, const char* message, int pos_x, int pos_y);

unsigned char *mem_base;
int game_score = 0;

void init_model(){
    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
}

void advance_state(objects_t** objects, int obj_num){

    move_space_ship(objects[SPACE_SHIP]->objects);

    int *i = &(objects[ALIENS]->curr_obj_idx);
    while((*i) < objects[ALIENS]->count){
        object_desc_t* alien = objects[ALIENS]->objects+*i;
        if(alien->status){

            move_alien(objects[ALIENS], *i);

            (*i)++;
            (*i) %= objects[ALIENS]->count;
            break;
        }
        (*i)++;
        (*i) %= objects[ALIENS]->count;
    }


    int* obj_pos_x = get_pos_x_of_objects(objects[SPACE_SHIP]->objects, objects[ALIENS]->objects, objects[BULLETS]->count);

    move_bullets(objects[BULLETS], obj_pos_x);

    detect_intersections(objects);
//    detect_hits(objects[ALIENS], objects[BULLETS]);

    update_game_text(objects[GAME_TEXT]);
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

void move_alien(objects_t* aliens, int curr_idx){
    object_desc_t* all_aliens = aliens->objects;
    object_desc_t* curr_alien = aliens->objects+curr_idx;
    int* speed_x = &aliens->speed_x;
    int* speed_y = &aliens->speed_y;

    if((*speed_y) == 0){
        curr_alien->pos_x+=(*speed_x);
    }

    if(curr_alien->pos_y+curr_alien->size_y+(*speed_y) > 320){
        printf("YOU LOST\n");
        exit(0);
    }
    curr_alien->pos_y+=(*speed_y);
//    printf("work\n");
    if(curr_idx == get_last_alive_alien_idx(aliens->objects, aliens->count)){
        printf("LAST\n");
        for(int i = 0; i < aliens->count; i++){
            if(!all_aliens[i].status){
                continue;
            }
            if(all_aliens[i].pos_x+all_aliens[i].size_x+(*speed_x) > 480 || all_aliens[i].pos_x+(*speed_x) < 0){
                (*speed_y) = 20;
                (*speed_x)*=-1;

                break;
            }
            (*speed_y) = 0;
        }
    }


}

int get_last_alive_alien_idx(object_desc_t* aliens, int aliens_num){
    int last_alive = aliens_num-1;

    while(last_alive > 0 && !(aliens+last_alive)->status){
        last_alive--;
    }
    if(!(aliens+last_alive)->status){
        printf("ERROR: is not alien alive here!\n");
        exit(1);
    }
    return last_alive;
}

int* get_pos_x_of_objects(object_desc_t* space_ship, object_desc_t* aliens, int obj_num){
    int* positions_x = malloc(obj_num*sizeof(int));

    positions_x[0] = space_ship->pos_x+space_ship->size_x/2-1;
    for(int i = 1; i < obj_num; i++){
        positions_x[i] = aliens[i].pos_x+aliens[i].size_x/2-1;
    }
    return positions_x;
}

void move_bullets(objects_t* bullets, int* positions_x){
    check_knob_presses(bullets->objects, positions_x[0]);

    if(bullets->objects[0].status){
        move_space_ship_bullet(bullets->objects);
    }

    for(int i = 1; i < bullets->count; i++){
        if(bullets->objects[i].status){
            move_alien_bullet(bullets->objects+i);
        }
    }
}

void check_knob_presses(object_desc_t* bullet, int pos_x){
    uint32_t r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    if(!bullet->status && (r & 0x7000000) != 0){
        bullet->status = true;
        bullet->pos_x = pos_x;
        bullet->pos_y = 291;
        printf("KNOB WAS PRESSED\n");
    }
}

void move_space_ship_bullet(object_desc_t* bullet){
    if(bullet->pos_y-4 <= 0){
        bullet->status = false;
        return;
    }
    uint32_t b = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    uint32_t r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

//    printf("%d\n", (int)(((r>>16)&0xff)*320)/256);
//    printf("%d\n", (int)((b&0xff)*480)/256);

    bullet->pos_y = (int)(((r>>16)&0xff)*320)/256;
    bullet->pos_x = (int)((b&0xff)*480)/256;
//    bullet->pos_y-=4;
}

void move_alien_bullet(object_desc_t* bullet){
    if(bullet->pos_y+2 <= 320){
        bullet->status = false;
        return;
    }
    bullet->pos_y+=2;
}

void detect_intersections(objects_t** objects){
    int wounded_obj;
    wounded_obj = detect_hits(objects[ALIENS], objects[BULLETS]->objects+0);
    if(wounded_obj != -1){
        objects[ALIENS]->objects[wounded_obj].status = false;
            switch (FIFTH_LINE-wounded_obj/ALIENS_IN_LINE) {
                case 0:
                    game_score+=30;
                    break;
                case 1:
                case 2:
                    game_score+=20;
                    break;
                case 3:
                case 4:
                    game_score+=10;
                    break;
            }
//        objects[BULLETS]->objects[0].status = false;
    }

    // return index of wounded object
    wounded_obj = detect_hits(objects[WALLS], objects[BULLETS]->objects+0);
    if(wounded_obj != -1){
        objects[WALLS]->objects[wounded_obj].status--;
        if(objects[WALLS]->objects[wounded_obj].status != false){
            // set next texture (the wall is cracked)
            objects[WALLS]->objects[wounded_obj].bits+=objects[WALLS]->objects[wounded_obj].bit_height;
        }

        objects[BULLETS]->objects[0].status = false;
    }


//    for(int i = 1; i < objects[BULLETS]->count; i++){
//        detect_hits(objects[ALIENS], objects[BULLETS]->objects+i);
//    }



}

int detect_hits(objects_t* objects, object_desc_t* bullet){

    for(int i = 0; i < objects->count; i++){

        object_desc_t* object = objects->objects + i;

        if(object->status && bullet->status &&
           bullet->pos_y <= object->pos_y + object->size_y - 1 &&
            bullet->pos_y+bullet->size_y-1 >= object->pos_y &&
            bullet->pos_x+bullet->size_x-1 >= object->pos_x &&
           bullet->pos_x <= object->pos_x + object->size_x - 1)
        {
//            object->status = false;
//            switch (FIFTH_LINE-i/ALIENS_IN_LINE) {
//                case 0:
//                    game_score+=30;
//                    break;
//                case 1:
//                case 2:
//                    game_score+=20;
//                    break;
//                case 3:
//                case 4:
//                    game_score+=10;
//                    break;
//            }

//            space_ship_bullet->status = false;
            return i;
        }
    }
    return -1;
}

void update_game_text(objects_t* game_text){

    for(int i = 0; i < game_text->count; i++){
        game_text->objects[i].status = false;
    }

    char message[10000];

    sprintf(message, "%d", game_score);
    write_message(game_text, message, 30, 10);

//    sprintf(message, "HI_SCORE");
//    write_message(game_text, message, 100, 100);
    game_text->curr_obj_idx = 0;
}

void write_message(objects_t* text, const char* message, int pos_x, int pos_y){
    object_desc_t* curr_char = text->objects+text->curr_obj_idx;

    int i = 0;
    while(message[i] != '\0'){
        if(text->curr_obj_idx+i > text->count){
            curr_char = text->objects+0;
        }

        int char_number = message[i] - '0';
//        printf("work\n");
        curr_char[i].status = true;
        curr_char[i].bit_width = char_width[char_number];
        curr_char[i].bit_height = char_height[0];
        curr_char[i].size_x  = curr_char[i].bit_width * curr_char[i].scale;

        if(pos_x+curr_char[i].size_x+curr_char[i].size_x > 480){
            pos_y+=curr_char[i].size_y;

            if(pos_y + curr_char[i].size_y > 320){
                pos_y = 10;

            }
            pos_x = 0;
        }
        curr_char[i].pos_x = pos_x;
        curr_char[i].pos_y = pos_y;

        pos_x+=curr_char[i].size_x;

        curr_char[i].bits =  char_bits + char_number*curr_char[i].bit_height;
        i++;
    }
    text->curr_obj_idx+=i;
    text->curr_obj_idx%=text->count;
}