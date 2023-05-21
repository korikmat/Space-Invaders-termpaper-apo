#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "model.h"
#include "kit_tools/mzapo_phys.h"
#include "kit_tools/mzapo_regs.h"
#include "textures/font_texture.h"
#include "game_objects/aliens.h"

void move_space_ship(object_desc_t* space_ship);
int get_pos_x_from_knob();

bool is_alien_dying(objects_t* aliens);
void move_aliens(objects_t* aliens);
void move_alive_alien(objects_t * aliens, int curr_idx);
int get_last_alive_alien_idx(object_desc_t* aliens, int aliens_num);

void get_pos_x_of_objects(int* obj_pos_x, object_desc_t* space_ship, object_desc_t* aliens, int obj_num);
void move_bullets(objects_t* bullets, int* positions_x);
void check_knob_presses(object_desc_t* bullet, int pos_x);
void move_space_ship_bullet(object_desc_t* bullet);
void move_alien_bullet(object_desc_t* bullet);

void detect_intersections(objects_t** objects);
int detect_hits(objects_t* objects, object_desc_t* bullet);

void actualize_lives(objects_t* lives);

void update_texture(objects_t** objects);

void update_game_text(objects_t* game_text);
void write_message(objects_t* text, const char* message, int pos_x, int pos_y);



unsigned char *mem_base;
int game_score = 0;
int lives_left = 3;

int frames1 = 0;
struct timeval start_time1, end_time1;
double elapsed_time1;

void init_model(){
    gettimeofday(&start_time1, NULL);

    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
}

void advance_state(objects_t** objects, int obj_num){
    if(lives_left == 0){
        printf("YOU DIED!\n");
        return;
    }

    move_space_ship(objects[SPACE_SHIP]->objects);

    if(is_alien_dying(objects[ALIENS]) == false){
        move_aliens(objects[ALIENS]);
    }

    int obj_pos_x[objects[BULLETS]->count];
    get_pos_x_of_objects(obj_pos_x, objects[SPACE_SHIP]->objects, objects[ALIENS]->objects, objects[BULLETS]->count);
    move_bullets(objects[BULLETS], obj_pos_x);

    detect_intersections(objects);
//    detect_hits(objects[ALIENS], objects[BULLETS]);
    actualize_lives(objects[LIVES]);

    update_game_text(objects[GAME_TEXT]);

    update_texture(objects);



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

bool is_alien_dying(objects_t* aliens){
    object_desc_t* alien;
    for(int i = 0; i < aliens->count; i++){
        alien = aliens->objects+i;

        if(alien->status < 0){
            alien->status++;
            return true;
        }
    }
    return false;
}

void move_aliens(objects_t* aliens){
    int *i = &(aliens->curr_obj_idx);
    int died_count = 0;
    while((*i) < aliens->count){
        object_desc_t* alien = aliens->objects+*i;
        if(alien->status){

            move_alive_alien(aliens, *i);

            (*i)++;
            (*i) %= aliens->count;
            break;
        }

        died_count++;
        if(died_count == aliens->count){
            return;
        }

        (*i)++;
        (*i) %= aliens->count;
    }
}

void move_alive_alien(objects_t* aliens, int curr_idx){
    object_desc_t* all_aliens = aliens->objects;
    object_desc_t* curr_alien = aliens->objects+curr_idx;
    int* speed_x = &aliens->speed_x;
    int* speed_y = &aliens->speed_y;

    if((*speed_y) == 0){
        curr_alien->pos_x+=(*speed_x);
        switch (curr_alien->status) {
            case 1:
                // curr_alien->bits++;
                curr_alien->status = 2;
                break;
            case 2:
                // curr_alien->bits++;
                curr_alien->status = 1;
        }
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
                (*speed_y) = 16;
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

void get_pos_x_of_objects(int* obj_pos_x, object_desc_t* space_ship, object_desc_t* aliens, int obj_num){

    obj_pos_x[0] = space_ship->pos_x+space_ship->size_x/2-1;
    for(int i = 1; i < obj_num; i++){
        obj_pos_x[i] = aliens[i].pos_x+aliens[i].size_x/2-1;
    }
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
    if(bullet->pos_y-8 <= 0){
        bullet->status = false;
        return;
    }
    uint32_t b = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    uint32_t r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

//    printf("%d\n", (int)(((r>>16)&0xff)*320)/256);
//    printf("%d\n", (int)((b&0xff)*480)/256);

//    bullet->pos_y = (int)(((r>>16)&0xff)*320)/256;
//    bullet->pos_x = (int)((b&0xff)*480)/256;
    bullet->pos_y-=8;
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
        objects[ALIENS]->objects[wounded_obj].status = -10;
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
       objects[BULLETS]->objects[0].status = false;
    }

    // return index of wounded object
    wounded_obj = detect_hits(objects[WALLS], objects[BULLETS]->objects+0);
    if(wounded_obj != -1){
        objects[WALLS]->objects[wounded_obj].status--;
        if(objects[WALLS]->objects[wounded_obj].status != false){
            // set next texture (the wall is cracked)
            // objects[WALLS]->objects[wounded_obj].bits+=objects[WALLS]->objects[wounded_obj].bit_height;
            // objects[WALLS]->objects[wounded_obj].bits_offset+= 1*objects[WALLS]->objects[wounded_obj].bit_height;
        }

        objects[BULLETS]->objects[0].status = false;
    }

//    for(int i = 0; i < objects[BULLETS]->count; i++){
//        wounded_obj = detect_hits(objects[SPACE_SHIP], objects[BULLETS]->objects+i);
//
//        if(wounded_obj != -1){
//
//            objects[BULLETS]->objects[0].status = false;
//            lives_left--;
//        }
//    }





    wounded_obj = detect_hits(objects[GAME_TEXT], objects[BULLETS]->objects+0);
    if(wounded_obj != -1){
        objects[GAME_TEXT]->objects[wounded_obj].status = -100;
        objects[BULLETS]->objects[0].status = false;
    }




//    for(int i = 1; i < objects[BULLETS]->count; i++){
//        detect_hits(objects[ALIENS], objects[BULLETS]->objects+i);
//    }



}

int detect_hits(objects_t* objects, object_desc_t* bullet){

    for(int i = 0; i < objects->count; i++){

        object_desc_t* object = objects->objects + i;

        if(object->status > 0 && bullet->status &&
           bullet->pos_y <= object->pos_y + object->size_y - 1 &&
            bullet->pos_y+bullet->size_y-1 >= object->pos_y &&
            bullet->pos_x+bullet->size_x-1 >= object->pos_x &&
           bullet->pos_x <= object->pos_x + object->size_x - 1)
        {
            return i;
        }
    }
    return -1;
}

void actualize_lives(objects_t* lives){
    if(lives_left < lives->count){
        lives->objects[lives_left].status = false;
    }
}

void update_texture(objects_t** objects){
    objects_t* aliens = objects[ALIENS];
    for(int i = 0; i < aliens->count; i++){
        switch (aliens->objects[i].status) {
            case 1:
                aliens->objects[i].bits_offset = 0*aliens->objects[i].bit_height;
                break;
            case 2:
                aliens->objects[i].bits_offset = 1*aliens->objects[i].bit_height;
                break;
            case -10:
                aliens->objects[i].bits_offset = -1*aliens->objects[i].bit_height;
                aliens->objects[i].bit_width = 13;
                break;
        }
    }

    objects_t* walls = objects[WALLS];

    for(int i = 0; i < walls->count; i++){
        switch (walls->objects[i].status){
            case 4:
                walls->objects[i].bits_offset = 0*walls->objects[i].bit_height;
                break;
            case 3:
                walls->objects[i].bits_offset = 1*walls->objects[i].bit_height;
                break;
            case 2:
                walls->objects[i].bits_offset = 2*walls->objects[i].bit_height;
                break;
            case 1:
                walls->objects[i].bits_offset = 3*walls->objects[i].bit_height;
                break;
        }
    }

    objects_t* game_text = objects[GAME_TEXT];
    for(int i = 0; i < game_text->count; i++){
        if(game_text->objects[i].status < 0){
//            printf("WOOOOOORK\n");
            game_text->objects[i].bits_offset = 0;
        }
//        switch (game_text->objects[i].status){
//            case -39:
//                printf("WOOOOOORK\n");
//                game_text->objects[i].bits_offset = 0;
//                break;
//        }
    }

}

void update_game_text(objects_t* game_text){

//    for(int i = 0; i < game_text->count; i++){
//        game_text->objects[i].status = false;
//    }

    char message[10000];

    sprintf(message, "SCORE<%d>", game_score);
    write_message(game_text, message, 30, 8);

    sprintf(message, "HI-SCORE<%d>", 10000);
    write_message(game_text, message, 260, 8);

//    sprintf(message, "QWERTYUIOPASDFGHJKLZXCVBNM qwertyuiopasdfghjklzxcvbnm <>=");
//    write_message(game_text, message, 0, 100);

    sprintf(message, "%d", lives_left);
    write_message(game_text, message, 5, 300);

    sprintf(message, "PINK FLOYD");
    write_message(game_text, message, 330, 300);

    frames1++;

    gettimeofday(&end_time1, NULL);
    elapsed_time1 = (end_time1.tv_sec - start_time1.tv_sec) + (end_time1.tv_usec - start_time1.tv_usec) / 1000000.0;

    if(elapsed_time1 >= 1.0){
        sprintf(message, "FPS %.2f", frames1 / elapsed_time1);
        write_message(game_text, message, 180, 300);
        frames1 = 0;
        start_time1 = end_time1;
    }

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

        int char_number = message[i] - ' ';
//        printf("work\n");
//        curr_char[i].status = true;
        curr_char[i].status++;

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

        curr_char[i].bits_offset =  char_number*curr_char[i].bit_height;
        i++;
    }
    text->curr_obj_idx+=i;
    text->curr_obj_idx%=text->count;
}