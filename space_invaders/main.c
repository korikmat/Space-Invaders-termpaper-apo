#include <stdlib.h>
#include <stdio.h>

#include "game_objects/bullets.h"
#include "game_objects/game_text.h"
#include "game_objects/menu_text.h"
#include "game_objects/walls.h"
#include "game_objects/lives.h"
#include "game_objects/flying_saucer.h"
#include "game_objects/aliens.h"
#include "game_objects/space_ship.h"
#include "game_model/model.h"
#include "game_view/view.h"

#define SUCCESSFUL_EXIT 0;
#define ERROR           101

#define OBJECTS_NUM (MENU_TEXT+1)

void prepare_for_exit(objects_t** objects, int obj_num);

int main(int argc, char *argv[]) {
    printf("The app is up and running!\n");

    printf("\nStarting creating objects...\n");
    // create all game objects
    objects_t** objects = (objects_t**)malloc(OBJECTS_NUM*sizeof(objects_t*));
    if(objects == NULL){
        fprintf(stderr, "ERROR: Cant allocate mem for objects!\n");
        exit(ERROR);
    }

    objects[ALIENS] = create_aliens();
    objects[ALIENS]->color = WHITE;

    objects[FLYING_SAUCER] = create_flying_saucer();
    objects[FLYING_SAUCER]->color = RED;

    objects[BULLETS] = create_bullets();
    objects[BULLETS]->color = WHITE;

    objects[SPACE_SHIP] = create_space_ship();
    objects[SPACE_SHIP]->color = RED;

    objects[WALLS] = create_walls();
    objects[WALLS]->color = WHITE;

    objects[LIVES] = create_lives();
    objects[LIVES]->color = WHITE;

    objects[GAME_TEXT] = create_game_text();
    objects[GAME_TEXT]->color = RED;

    objects[MENU_TEXT] = create_menu_text();
    objects[MENU_TEXT]->color = WHITE;

    // init model and view
    printf("\nStarting initializing...\n");
    init_model();
    prepare_menu_scene(objects, OBJECTS_NUM);
    init_drawing();

//    struct timespec loop_delay;
//    loop_delay.tv_sec = 0;
//    loop_delay.tv_nsec = 1000/10 * 1000 * 1000;
    printf( "\nStarting game loop...\n");
    int game_state = MENU;
    while(game_state != EXIT){
        render(objects, OBJECTS_NUM, game_state);

        if(game_state == MENU){
            game_state = process_menu(objects, OBJECTS_NUM);
            if(game_state == GAME){
                prepare_game_scene(objects);
            }
        }
        if(game_state == GAME){
            game_state = advance_state(objects);
            if(game_state == WIN){
                prepare_game_scene(objects);
                game_state = GAME;
            }
            if(game_state == MENU){
                prepare_menu_scene(objects, OBJECTS_NUM);
            }
        }
        if(game_state == EXIT){
            prepare_for_exit(objects, OBJECTS_NUM);
        }

//        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    return SUCCESSFUL_EXIT;
}

// clear all game objects
void prepare_for_exit(objects_t** objects, int obj_num){
    for(int i = 0; i < obj_num; i++){
        objects_t* object = objects[i];
        free(object->objects);
        free(object);
    }
    printf( "Goodbye:)\n");
}