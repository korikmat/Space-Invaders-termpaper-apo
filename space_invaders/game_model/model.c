#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "kit_tools/mzapo_phys.h"
#include "kit_tools/mzapo_regs.h"

#include "model.h"
#include "textures/font_texture.h"

#include "game_objects/space_ship.h"
#include "game_objects/aliens.h"
#include "game_objects/flying_saucer.h"
#include "game_objects/bullets.h"
#include "game_objects/walls.h"
#include "game_objects/lives.h"

#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 320

#define ERROR 101

#define LIVES_COUNT 3
#define LED32_LIVES_COUNT 0xffffffff

#define HI_SCORE_FILENAME "hi-score.txt"

#define MENU_BUTTONS_POS_X 28
#define MENU_BUTTONS_POS_Y 293

#define RED         0b1111100000000000;
#define LIGHT_GREEN 0x00000f00;
#define LIGHT_RED   0x000f0000;
#define WHITE       0b1111111111111111;

#define WOUNDED_ALIEN_STATUS (-10)
#define WOUNDED_FLYING_SAUCER_STATUS (-20)
#define WOUNDED_SPACE_SHIP_STATUS 50
#define WOUNDED_TEXT_STATUS (-50)

#define SCORE_POS_X         30
#define SCORE_POS_Y         0
#define HI_SCORE_POS_X      260
#define HI_SCORE_POS_Y      0
#define LIVES_POS_X         5
#define LIVES_POS_Y         300
#define PINK_FLOYD_POS_X    330
#define PINK_FLOYD_POS_Y    300
#define FPS_POS_X           180
#define FPS_POS_Y           300


bool lose();
bool win(objects_t* aliens);
bool stop();

void set_hi_score();

bool is_green_knob_pressed();

void reset_hi_score();

int get_pos_x_from_blue_knob();

bool is_alien_dying(objects_t* aliens);

void move_bullets(objects_t* bullets, objects_t* aliens, objects_t* space_ship);
bool is_red_knob_pressed();

void detect_intersections(objects_t** objects);
int detect_hits(objects_t* objects, object_desc_t* bullet);

void actualize_lives(objects_t* lives);

void update_textures(objects_t** objects);

void check_hi_game_score();

void update_game_text(objects_t* game_text);
void write_message(objects_t* text, const char* message, int pos_x, int pos_y);

void update_leds(objects_t** objects);
bool is_space_ship_dying(objects_t* space_ship);

void save_hi_score();


unsigned char *mem_base;
int score = 0;
int hi_score = 0;
int lives_left = LIVES_COUNT;
uint32_t led32_lives = LED32_LIVES_COUNT;

int frames = 0;
struct timeval start_time, end_time;
double elapsed_time;

/* Allocates memory to the board and sets the hi-score */
void init_model(){
    gettimeofday(&start_time, NULL);
    srandom(time(NULL));

    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    set_hi_score();
    printf("Model was init successfully!\n");

}

/* Tries to open the file with the highest score, if the file is not found, sets the highest score to 1*/
void set_hi_score(){
    FILE *hi_score_file = fopen(HI_SCORE_FILENAME, "rb");
    if (hi_score_file != NULL) {
        if(fread(&hi_score, sizeof(int), 1, hi_score_file) != 1){
            fprintf(stderr, "Problems with hi-score file, reset hi-score to 0\n");
            hi_score = 0;
        }
        else{
            printf("Hi-score was loaded from file!\n");
        }
        fclose(hi_score_file);
    } else {
        fprintf(stderr, "Problems with hi-score file, reset hi-score to 0\n");
        hi_score = 0;
    }
}

/* Processes the main menu*/
int process_menu(objects_t** objects, int obj_num){
    int ret = MENU;
    uint32_t r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    objects[MENU_TEXT]->curr_obj_idx = 0;
    objects[MENU_TEXT]->color = WHITE;

    char message[100];
                            // get green knob value
    int green_knob_value = (int)(((r&0xff00)>>8)/4)%4;
    switch (green_knob_value) {
        case 0:
            if(is_green_knob_pressed()){
                printf("Starting GAME scene...\n");
                ret = GAME;
            }
            sprintf(message, "PLAY");
            write_message(objects[MENU_TEXT], message, MENU_BUTTONS_POS_X, MENU_BUTTONS_POS_Y);

            break;
        case 1:
            sprintf(message, "HI-SCORE<%d>", hi_score);
            write_message(objects[MENU_TEXT], message, MENU_BUTTONS_POS_X, MENU_BUTTONS_POS_Y);

            break;
        case 2:
            if(is_green_knob_pressed()){
                reset_hi_score();
                objects[MENU_TEXT]->color = RED;
            }
            sprintf(message, "RESET");
            write_message(objects[MENU_TEXT], message, MENU_BUTTONS_POS_X, MENU_BUTTONS_POS_Y);

            break;
        case 3:
            sprintf(message, "EXIT");
            write_message(objects[MENU_TEXT], message, MENU_BUTTONS_POS_X, MENU_BUTTONS_POS_Y);
            if(is_green_knob_pressed()){
                printf("Exiting game...\n");
                ret = EXIT;
            }

            break;
        default:
            fprintf(stderr, "ERROR: Unknown green knob value!\n");
            exit(ERROR);
    }
    for(int i = objects[MENU_TEXT]->curr_obj_idx; i < objects[MENU_TEXT]->count; i++){
        objects[MENU_TEXT]->objects[i].status = false;
    }

    return ret;
}

/* If green knob is pressed
 * return true if is pressed, false otherwise*/
bool is_green_knob_pressed(){
    uint32_t knobs = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    return (knobs & 0x2000000)>>25 == 1;
}

/* Prepares objects to be displayed on the game stage*/
void prepare_game_scene(objects_t** objects){
    printf( "\nPreparing game scene...\n");
    // clear menu text
    for(int i = 0; i < objects[MENU_TEXT]->count; i++){
        objects[MENU_TEXT]->objects[i].status = false;
    }
    printf( "Menu text was cleared!\n");

    //prepare aliens
    reset_aliens(objects[ALIENS]);
    printf( "Aliens was reset!\n");
    //prepare walls
    reset_walls(objects[WALLS]);
    printf( "Walls was reset!\n");
    //prepare lives
    reset_lives(objects[LIVES]);
    if(lives_left == 0){
        score = 0;
        lives_left = LIVES_COUNT;
    }
    led32_lives = 0x00000001;
    printf( "Lives was reset!\n");

    //prepare spaceship
    reset_space_ship(objects[SPACE_SHIP]);
    printf( "Spaceship was reset!\n");
    printf( "Game was prepared!\n");

}

/* Prepares objects before displaying the main menu*/
void prepare_menu_scene(objects_t** objects, int obj_num){
    printf( "Preparing menu scene...\n");
    // go through all objects and set visible to 0
    for(int i = 0; i < obj_num; i++){
        objects_t* object = objects[i];
        for(int j = 0; j < object->count; j++){
            object->objects[j].status = false;
        }
    }
    printf( "All objects was cleared!\n");

    // disable all LEDs
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_LINE_o) = 0;
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0;
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0;
    printf( "Menu was prepared!\n");

}

/* Opens the file with the hi-score and resets it to 0*/
void reset_hi_score(){
    hi_score = 0;
    printf("Resetting hi-score!\n");
    FILE* hi_score_file = fopen("hi-score.txt", "wb");
    if (hi_score_file != NULL) {
        if(fwrite(&hi_score, sizeof(int), 1, hi_score_file) != 1){
            fprintf(stderr, "ERROR: Cant write hi-score to file!\n");
            fclose(hi_score_file);
        }
        fclose(hi_score_file);
    } else {
        fprintf(stderr, "ERROR: Cant open hi-score file!\n");
    }
}

/* Basic Game Function. It is where the basic logic takes place.
 * return: 1 if game continuing, -1 if game was lost, 0 if game was win*/
int advance_state(objects_t** objects){
    int ret = GAME;

    if(lose()){
        ret = MENU;
        return ret;
    }
    if(win(objects[ALIENS])){
        ret = WIN;
        return ret;
    }

    // move objects
    move_space_ship(objects[SPACE_SHIP]->objects, get_pos_x_from_blue_knob());

    if(!is_alien_dying(objects[ALIENS])){
        if(move_aliens(objects[ALIENS])){
            lives_left = 0;
            ret = MENU;
        }
    }

    move_flying_saucer(objects[FLYING_SAUCER]);

    move_bullets(objects[BULLETS], objects[ALIENS], objects[SPACE_SHIP]);
    // detect hits
    detect_intersections(objects);
    // synchronize the object of lives and lives
    actualize_lives(objects[LIVES]);
    // if the current score is greater than hi-score
    check_hi_game_score();
    // update all text in game
    update_game_text(objects[GAME_TEXT]);
    // update textures for all objects
    update_textures(objects);
    // update RGB LEDs and LED32
    update_leds(objects);
    // if blue knob was pressed
    if(stop()){
        ret = MENU;
    }

    return ret;

}
/* Check if lives on LED32 is 0
 * return true if is 0, false otherwise*/
bool lose(){
    bool ret = false;
    if(led32_lives == 0){
        printf("You lost!\n");
        save_hi_score();

        ret = true;
    }
    return ret;
}
/* Check if is alive aliens
 * return true if is 0 alive aliens, false otherwise*/
bool win(objects_t* aliens){
    bool ret = false;

    // go through all aliens to find alive
    int alive_aliens_n = 0;
    for(int i = 0; i < aliens->count; i++){
        object_desc_t alien = aliens->objects[i];
        if(alien.status != 0){
            alive_aliens_n++;
        }
    }
    // if alive alien wasn't found
    if(alive_aliens_n == 0){
        printf("All aliens was killed!\n");
        ret = true;
    }
    return ret;
}
/* Get position x on display from blue knob value*/
int get_pos_x_from_blue_knob(){
    uint32_t r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    return (int)((r&0xff)*480)/256;
}

/* Check if is dying aliens
 * return true if alien is dying, false otherwise*/
bool is_alien_dying(objects_t* aliens){
    bool ret = false;
    // go through all aliens to find anyone with status < 0
    object_desc_t* alien;
    for(int i = 0; i < aliens->count; i++){
        alien = aliens->objects+i;

        if(alien->status < 0){
//            alien->status++;
            ret = true;
        }
    }
    return ret;
}
/* Check if is spaceship dying
 * return true if is spaceship dying, false otherwise*/
bool is_space_ship_dying(objects_t* space_ship){
    bool ret = false;

    object_desc_t* space_ship_desc = space_ship->objects;
    if(space_ship_desc->status > 1){
        space_ship_desc->status--;
        ret = true;

    }
    return ret;
}

/* Try to move spaceship and aliens bullets*/
void move_bullets(objects_t* bullets, objects_t* aliens, objects_t* space_ship){
    int bullet_pos_x = space_ship->objects->pos_x+space_ship->objects->size_x/2;
    move_space_ship_bullet(bullets->objects, bullet_pos_x, is_red_knob_pressed());
    try_to_attack_space_ship(bullets, aliens);
}

/* Check if red knob is pressed
 * return true if is pressed, false otherwise*/
bool is_red_knob_pressed(){
    uint32_t r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    return (r & 0x4000000) != 0;
}

/* Check all intersections*/
void detect_intersections(objects_t** objects){
    int wounded_obj;
    // return index of wounded object
    wounded_obj = detect_hits(objects[ALIENS], objects[BULLETS]->objects+0);
    if(wounded_obj != -1){
        objects[ALIENS]->objects[wounded_obj].status = WOUNDED_ALIEN_STATUS;

        score+=objects[ALIENS]->objects[wounded_obj].cost;
        objects[BULLETS]->objects[0].status = false;
    }


    wounded_obj = detect_hits(objects[FLYING_SAUCER], objects[BULLETS]->objects+0);
    if(wounded_obj != -1){
        objects[FLYING_SAUCER]->objects->status = WOUNDED_FLYING_SAUCER_STATUS;


        int coefficient = random()%3;
        objects[FLYING_SAUCER]->objects->cost = 50 + 50 * coefficient;
        score+=objects[FLYING_SAUCER]->objects->cost;


        objects[BULLETS]->objects[0].status = false;

    }

    for(int i = 0; i < objects[BULLETS]->count; i++){
        if(i > 0){
            wounded_obj = detect_hits(objects[SPACE_SHIP], objects[BULLETS]->objects+i);
            if(wounded_obj != -1){
                printf("Spaceship was attacked!\n");
                objects[SPACE_SHIP]->objects->status = WOUNDED_SPACE_SHIP_STATUS;
                objects[BULLETS]->objects[i].status = false;

                lives_left--;
            }
        }
        wounded_obj = detect_hits(objects[GAME_TEXT], objects[BULLETS]->objects+i);
        if(wounded_obj != -1){
            objects[GAME_TEXT]->objects[wounded_obj].status = WOUNDED_TEXT_STATUS;

            objects[BULLETS]->objects[i].status = false;
        }

        wounded_obj = detect_hits(objects[WALLS], objects[BULLETS]->objects+i);
        if(wounded_obj != -1){
            objects[WALLS]->objects[wounded_obj].status--;

            objects[BULLETS]->objects[i].status = false;
        }
    }

}
/* Looks at the intersection of the objects specified in the arguments
 * return the index of the object the bullet intersected with*/
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

/* Synchronise left lives with objects lives */
void actualize_lives(objects_t* lives){
    if(lives_left < lives->count){
        lives->objects[lives_left].status = false;
    }
}
/* Updates the textures of all game objects*/
void update_textures(objects_t** objects){
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
//                aliens->objects[i].bit_width = 13;
                break;
        }
        if(aliens->objects[i].status < 0){
            aliens->objects[i].status++;
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
    object_desc_t* flying_saucer = objects[FLYING_SAUCER]->objects;
    switch (flying_saucer->status) {
        case 0:
            flying_saucer->bits_offset = 0;
            flying_saucer->bit_width = 16;
            flying_saucer->bit_height = 7;
            flying_saucer->size_x = flying_saucer->bit_width*flying_saucer->scale;
            flying_saucer->size_y = flying_saucer->bit_height*flying_saucer->scale;
            break;
        case -10:
            flying_saucer->bits_offset+=1*flying_saucer->bit_height;
            break;
        case -20:
            flying_saucer->bits_offset = 1*flying_saucer->bit_height;
            flying_saucer->bit_width = 20;
            flying_saucer->bit_height = 8;
            flying_saucer->size_x = flying_saucer->bit_width*flying_saucer->scale;

            flying_saucer->size_y = flying_saucer->bit_height*flying_saucer->scale;
            break;
    }
    if(flying_saucer->status < 0){
        if(flying_saucer->status >= WOUNDED_FLYING_SAUCER_STATUS/2){
            char message[10];
            sprintf(message, "%d", flying_saucer->cost);
            write_message(objects[GAME_TEXT], message, flying_saucer->pos_x, flying_saucer->pos_y);
        }
        flying_saucer->status++;
    }

    objects_t* game_text = objects[GAME_TEXT];
    for(int i = 0; i < game_text->count; i++){
        if(game_text->objects[i].status < 0){
            game_text->objects[i].bits_offset = 0;
        }
    }

}

/* Update hi-score if the current score is greater than hi-score*/
void check_hi_game_score(){
    hi_score = score > hi_score ? score : hi_score;
}

/* Update all text in game*/
void update_game_text(objects_t* game_text){
    game_text->curr_obj_idx = 0;

    char message[1000];

    sprintf(message, "SCORE<%d>", score);
    write_message(game_text, message, SCORE_POS_X, SCORE_POS_Y);

    sprintf(message, "HI-SCORE<%d>", hi_score);
    write_message(game_text, message, HI_SCORE_POS_X, HI_SCORE_POS_Y);

    sprintf(message, "%d", lives_left);
    write_message(game_text, message, LIVES_POS_X, LIVES_POS_Y);

    sprintf(message, "PINK FLOYD");
    write_message(game_text, message, PINK_FLOYD_POS_X, PINK_FLOYD_POS_Y);

    // Displaying FPS
    frames++;

    gettimeofday(&end_time, NULL);
    elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    if(elapsed_time >= 1.0){
        for(int i = game_text->curr_obj_idx; i < game_text->count; i++){
            game_text->objects[i].status = false;
        }
        sprintf(message, "FPS<%.2f>", frames / elapsed_time);
        write_message(game_text, message, FPS_POS_X, FPS_POS_Y);
        frames = 0;
        start_time = end_time;
    }

}

/* Fills an array of text objects with appropriate characters*/
void write_message(objects_t* text, const char* message, int pos_x, int pos_y){
    object_desc_t* curr_char = text->objects+text->curr_obj_idx;

    int i = 0;
    while(message[i] != '\0'){
        if(text->curr_obj_idx+i > text->count){
            curr_char = text->objects+0;
        }

        int char_number = message[i] - ' ';

        curr_char[i].status++;

        curr_char[i].bits = char_bits;
        curr_char[i].bit_width = char_width[char_number];
        curr_char[i].bit_height = char_height[0];
        curr_char[i].size_x  = curr_char[i].bit_width * curr_char[i].scale;

        if(pos_x+curr_char[i].size_x+curr_char[i].size_x > DISPLAY_WIDTH){
            pos_y+=curr_char[i].size_y;

            if(pos_y + curr_char[i].size_y > DISPLAY_HEIGHT){
                pos_y = 0;

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
/*Checks if the blue knob was pressed
 * return true if was pressed, false otherwise*/
bool stop(){
    bool ret = false;
    uint32_t r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    // if blue knob pressed
    if((r & 0x1000000)>>24 == 1 ){
            save_hi_score();
            score = 0;
            lives_left = 0;
        ret = true;
    }
    return ret;

}

/* Saves the hi-score to a text file*/
void save_hi_score(){
    printf("Saving hi-score!\n");
    FILE* hi_score_file = fopen("hi-score.txt", "wb");
    if (hi_score_file != NULL) {
        if(fwrite(&hi_score, sizeof(int), 1, hi_score_file) != 1){
            fprintf(stderr, "ERROR: Cant write hi-score to file!\n");
            fclose(hi_score_file);
        }
        fclose(hi_score_file);
    } else {
        fprintf(stderr, "ERROR: Cant open hi-score file!\n");
    }
}

/* Update RGB LEDs and LED32*/
void update_leds(objects_t** objects){
    // update LED32
    switch (lives_left) {
        case 1:             //11 LEDs out of 32
            if (led32_lives > 0x000007ff){
                led32_lives = led32_lives>>1;
            }
            if (led32_lives < 0x000007ff){
                led32_lives = led32_lives<<1 | 0x1;
            }
            break;
        case 2:             //21 LEDs out of 32
            if (led32_lives > 0x001fffff){
                led32_lives = led32_lives>>1;
            }
            if (led32_lives < 0x001fffff){
                led32_lives = led32_lives<<1 | 0x1;
            }
            break;
        case 3:             //32 LEDs out of 32
            if (led32_lives < 0xffffffff){
                led32_lives = led32_lives<<1 | 0x1;
            }
            break;
        default:
            if (led32_lives > 0x0){
                led32_lives = led32_lives>>1;
            }
    }
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_LINE_o) = led32_lives;

    // update RGB1 LED
    if(is_alien_dying(objects[ALIENS])){
        *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = LIGHT_GREEN;
    } else{
        *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0x0;
    }

    // update RGB2 LED
    if(is_space_ship_dying(objects[SPACE_SHIP])){
        *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = LIGHT_RED;
    } else{
        *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0x0;
    }

}


